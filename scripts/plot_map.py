import pandas as pd
import numpy as np
import math
import urllib
import io
import os
import ssl
import warnings
import threading
from PIL import Image

# 屏蔽PIL调色板透明度警告，已主动做RGB转换，该警告无实际影响
warnings.filterwarnings("ignore", message="Palette images with Transparency expressed in bytes should be converted to RGBA images")


def deg2num(lat_deg, lon_deg, zoom):
    lat_rad = math.radians(lat_deg)
    n = 2.0 ** zoom
    xtile = int((lon_deg + 180.0) / 360.0 * n)
    ytile = int((1.0 - math.log(math.tan(lat_rad) + (1 / math.cos(lat_rad))) / math.pi) / 2.0 * n)
    return (xtile, ytile)


def num2deg(xtile, ytile, zoom):
    n = 2.0 ** zoom
    lon_deg = xtile / n * 360.0 - 180.0
    lat_rad = math.atan(math.sinh(math.pi * (1 - 2 * ytile / n)))
    lat_deg = math.degrees(lat_rad)
    return (lat_deg, lon_deg)


def getImageCluster(lon_deg, lat_deg, delta_long, delta_lat, zoom, style,
                    printlog, imgsavepath, apikey='', access_token='',
                    styleid='cjrewwj3l2dwt2tptkiu09scd'):
    tile_urls = {
        1: f'https://a.tile.thunderforest.com/cycle/{{0}}/{{1}}/{{2}}.png?apikey={apikey}',
        2: f'https://a.tile.thunderforest.com/transport/{{0}}/{{1}}/{{2}}.png?apikey={apikey}',
        3: r'https://tile-b.openstreetmap.fr/hot/{0}/{1}/{2}.png',
        4: r'https://webrd01.is.autonavi.com/appmaptile?lang=zh_cn&size=1&scale=1&style=8&x={1}&y={2}&z={0}',
        5: r'https://stamen-tiles.a.ssl.fastly.net/toner/{0}/{1}/{2}.png',
        6: r'https://stamen-tiles.a.ssl.fastly.net/watercolor/{0}/{1}/{2}.png',
        7: f'https://api.mapbox.com/styles/v1/ni1o1/{styleid}/tiles/256/{{0}}/{{1}}/{{2}}?access_token={access_token}'
    }
    
    if style not in tile_urls:
        raise ValueError(f"不支持的style值: {style}，可选范围 1-7")
    
    smurl = tile_urls[style]
    
    if style == 7:
        if styleid == 'dark':
            styleid = 'cjetnd20i1vbi2qqxbh0by7p8'
            smurl = f'https://api.mapbox.com/styles/v1/ni1o1/{styleid}/tiles/256/{{0}}/{{1}}/{{2}}?access_token={access_token}'
        elif styleid == 'light':
            styleid = 'cjrewwj3l2dwt2tptkiu09scd'
            smurl = f'https://api.mapbox.com/styles/v1/ni1o1/{styleid}/tiles/256/{{0}}/{{1}}/{{2}}?access_token={access_token}'

    xmin, ymax = deg2num(lat_deg, lon_deg, zoom)
    xmax, ymin = deg2num(lat_deg + delta_lat, lon_deg + delta_long, zoom)

    imgsize = 256
    Cluster = Image.new('RGB', ((xmax - xmin + 1) * imgsize - 1, (ymax - ymin + 1) * imgsize - 1))
    paste_lock = threading.Lock()
    ssl_context = ssl._create_unverified_context()

    def get_img(smurl, zoom, xtile, ytile, imgsize, imgsavepath):
        tile_dir = os.path.join(imgsavepath, 'tileimg')
        filename = f"{style}{styleid}-{zoom}-{xtile}-{ytile}-{imgsize}.png"
        tile_path = os.path.join(tile_dir, filename)

        def loadfig():
            try:
                if os.path.exists(tile_path):
                    return Image.open(tile_path).convert('RGB')
                return None
            except Exception:
                return None

        def savefig(tile):
            try:
                os.makedirs(tile_dir, exist_ok=True)
                tile.save(tile_path)
                if printlog:
                    print(f'figsaved: {filename}')
            except Exception:
                pass

        tile = loadfig()
        if tile is not None:
            with paste_lock:
                Cluster.paste(tile, box=((xtile - xmin) * imgsize, (ytile - ymin) * imgsize))
            return

        for t in range(10):
            try:
                imgurl = smurl.format(zoom, xtile, ytile)
                imgstr = urllib.request.urlopen(imgurl, timeout=10, context=ssl_context).read()
                tile = Image.open(io.BytesIO(imgstr)).convert('RGB')
                savefig(tile)
                with paste_lock:
                    Cluster.paste(tile, box=((xtile - xmin) * imgsize, (ytile - ymin) * imgsize))
                return
            except Exception as e:
                if printlog:
                    print(f'瓦片下载重试 {t+1}, 错误: {str(e)[:50]}')
        
        print(f"瓦片下载失败: zoom={zoom}, x={xtile}, y={ytile}")

    threads = []
    for xtile in range(xmin, xmax + 1):
        for ytile in range(ymin, ymax + 1):
            threads.append(threading.Thread(
                target=get_img,
                args=(smurl, zoom, xtile, ytile, imgsize, imgsavepath)
            ))
    
    for t in threads:
        t.daemon = True
        t.start()
    for t in threads:
        t.join()

    return Cluster


def plot_map(plt, bounds, zoom, style, imgsavepath=r'E:\GIS_Learning\data\maptileimg',
             printlog=False, apikey='', access_token='', styleid='dark'):
    try:
        os.makedirs(imgsavepath, exist_ok=True)
    except Exception:
        print('imgsavepath 无法创建，瓦片将不缓存')

    lon1, lat1, lon2, lat2 = bounds[0], bounds[1], bounds[2], bounds[3]
    
    a = getImageCluster(
        lon1, lat1, lon2 - lon1, lat2 - lat1,
        zoom, style, printlog=printlog, imgsavepath=imgsavepath,
        apikey=apikey, access_token=access_token, styleid=styleid
    )

    x_tile_1, y_tile_1 = deg2num(lat1, lon1, zoom)
    x_tile_2, y_tile_2 = deg2num(lat2, lon2, zoom)
    lat_min, lon_min = num2deg(x_tile_1, y_tile_1 + 1, zoom)
    lat_max, lon_max = num2deg(x_tile_2 + 1, y_tile_2, zoom)

    plt.imshow(np.asarray(a), extent=(lon_min, lon_max, lat_min, lat_max))


def plotscale(ax, bounds, textcolor='k', textsize=8, compasssize=1,
              accuracy='auto', rect=[0.1, 0.1], unit="KM", style=1):
    import math
    from shapely.geometry import Polygon
    import geopandas as gpd

    lon1, lat1, lon2, lat2 = bounds[0], bounds[1], bounds[2], bounds[3]

    if accuracy == 'auto':
        accuracy = (int((lon2 - lon1) / 0.0003 / 1000 + 0.5) * 1000)

    a, c = rect
    b = 1 - a
    d = 1 - c
    alon = (b * lon1 + a * lon2) / (a + b)
    alat = (d * lat1 + c * lat2) / (c + d)

    deltaLon = accuracy * 360 / (2 * math.pi * 6371004 * math.cos((lat1 + lat2) * math.pi / 360))

    if style == 1:
        scale = gpd.GeoDataFrame({
            'color': [(0,0,0), (1,1,1), (0,0,0), (1,1,1)],
            'geometry': [
                Polygon([(alon, alat), (alon+deltaLon, alat),
                         (alon+deltaLon, alat+deltaLon*0.4), (alon, alat+deltaLon*0.4)]),
                Polygon([(alon+deltaLon, alat), (alon+2*deltaLon, alat),
                         (alon+2*deltaLon, alat+deltaLon*0.4), (alon+deltaLon, alat+deltaLon*0.4)]),
                Polygon([(alon+2*deltaLon, alat), (alon+4*deltaLon, alat),
                         (alon+4*deltaLon, alat+deltaLon*0.4), (alon+2*deltaLon, alat+deltaLon*0.4)]),
                Polygon([(alon+4*deltaLon, alat), (alon+8*deltaLon, alat),
                         (alon+8*deltaLon, alat+deltaLon*0.4), (alon+4*deltaLon, alat+deltaLon*0.4)])
            ]
        })
        scale.plot(ax=ax, edgecolor=(0,0,0,1), facecolor=scale['color'], lw=0.6)

        unit_factor = 1000 if unit.upper() == 'KM' else 1
        for val in [1, 2, 4, 8]:
            x_pos = alon + val * deltaLon
            ax.annotate(
                str(int(val * accuracy / unit_factor)),
                color=textcolor, size=textsize,
                xy=(x_pos, alat + deltaLon*0.2),
                xytext=(-textsize*3/5, textsize/1.5),
                textcoords='offset points'
            )
        ax.annotate(
            unit, size=textsize, color=textcolor,
            xy=(alon + 8*deltaLon, alat + deltaLon*0.1),
            xytext=(textsize*2/5, -textsize/5),
            textcoords='offset points'
        )

    elif style == 2:
        scale = gpd.GeoDataFrame({
            'color': [(0,0,0), (1,1,1)],
            'geometry': [
                Polygon([(alon+deltaLon, alat), (alon+4*deltaLon, alat),
                         (alon+4*deltaLon, alat+deltaLon*0.4), (alon+deltaLon, alat+deltaLon*0.4)]),
                Polygon([(alon+4*deltaLon, alat), (alon+8*deltaLon, alat),
                         (alon+8*deltaLon, alat+deltaLon*0.4), (alon+4*deltaLon, alat+deltaLon*0.4)])
            ]
        })
        scale.plot(ax=ax, edgecolor=(0,0,0,1), facecolor=scale['color'], lw=0.6)

        unit_factor = 1000 if unit.upper() == 'KM' else 1
        for val in [4, 8]:
            x_pos = alon + val * deltaLon
            ax.annotate(
                str(int(val * accuracy / unit_factor)),
                color=textcolor, size=textsize,
                xy=(x_pos, alat + deltaLon*0.2),
                xytext=(-textsize*3/5, textsize/1.5),
                textcoords='offset points'
            )
        ax.annotate(
            unit, size=textsize, color=textcolor,
            xy=(alon + 8*deltaLon, alat + deltaLon*0.1),
            xytext=(textsize*2/5, -textsize/5),
            textcoords='offset points'
        )

    deltaLon_compass = compasssize * deltaLon
    alon_compass = alon - deltaLon_compass
    compass = gpd.GeoDataFrame({
        'color': [(0,0,0), (1,1,1)],
        'geometry': [
            Polygon([[alon_compass, alat], [alon_compass, alat+deltaLon_compass],
                     [alon_compass+1/2*deltaLon_compass, alat-1/2*deltaLon_compass]]),
            Polygon([[alon_compass, alat], [alon_compass, alat+deltaLon_compass],
                     [alon_compass-1/2*deltaLon_compass, alat-1/2*deltaLon_compass]])
        ]
    })
    compass.plot(ax=ax, edgecolor=(0,0,0,1), facecolor=compass['color'], lw=0.6)
    ax.annotate(
        'N', color=textcolor, size=textsize,
        xy=[alon_compass, alat + deltaLon_compass],
        xytext=(-textsize*2/5, textsize/2),
        textcoords='offset points'
    )
#!/usr/bin/env python
# coding=utf-8
import math
import matplotlib.pyplot as plt
import numpy as np
import random
import sys
reload(sys)
sys.setdefaultencoding('utf-8')

plt.rcParams['font.sans-serif'] = ['SimHei'] # 指定默认字体
plt.rcParams['axes.unicode_minus'] = False # 解决保存图像是负号'-'显示为方块的问题

station = [
    ["开封", "商丘", "周口", "南阳", "焦作", "荆州", "宜昌", "漯河", "孝感", "麻城"],
    [0,146,152,307,144,628,670,179,498,43],
    [146,0,140,372,275,692,735,202,496,433],
    [152,140,0,237,268,557,600,62,361,308],
    [307,372,237,0,329,334,376,175,343,389],
    [144,275,268,329,0,657,699,229,555,578],
    [628,692,557,334,657,0,152,501,209,328],
    [670,735,600,376,699,152,0,546,298,422],
    [179,202,62,175,229,501,546,0,330,355],
    [498,496,361,343,555,209,298,330,0,129],
    [439,433,308,389,578,328,422,355,129,0],
]
warehouse = [
    [ '郑州', '信阳', '武汉'], 
    [ 900, 700, 1000],
    [ 78,200,168,257,86,561,633,145,469,492],
    [ 353,349,205,186,400,332,400,174,170,180],
    [ 525,520,365,368,597,223,317,372,76,112],
]

mutaRule = 1
mutation = 0.02

times = 100 # 一个单位时间表示遗传一代

def initData():
    data = {}
    data['station'] = {}
    data['warehouse'] = {}
    data['ware_capacity'] = 30000
    data['car_max_dis'] = 1000
    data['car_capacity'] = 3000
    data['car_counter'] = 3
    data['dis_cost'] = 2
    data['alpha'] = 20
    data['beita'] = 10

    for index item in enumerate(station):
        if index == 0:
            data['station'] = {'name': item}
        else:
            name = data['station']['name'][index - 1]
            data['station'][name]['dis'] = item
    for index, item in enumerate(warehouse):
        if index == 0:
            data['warehouse'] = {'name': item}
        elif index == 1:
            for v_index, value in enumerate(item):
                print(data['warehouse']['name'])
                name = data['warehouse']['name'][v_index]
                data['warehouse'][name] = {'cost': value}
        else:
            name = data['warehouse']['name'][index - 2]
            data['warehouse'][name]['dis'] = item
    for key in data.keys():
        print(key, data[key])
    return data
'''
    colorList = ['green', 'blue', 'red', 'yellow', 'cyan', 'purple', 'pink', 'olive', 'gray', 'orange']
    for index, key in enumerate(data.keys()):
        for item in data[key]:
            plt.scatter(index, item, color=colorList[index])
    plt.xticks(range(0, 10), data.keys())
    plt.show()
'''

def raceTcost(race, station, warehouse):
    allplace = station['name']
    flag = random.shuffle(range(0 , len(allplace)))
    for index, place_num in flag:
        place = allplace[place_num]
        if index == 0: 
            # index == 0 从仓源去往一个地方
            dis = warehouse[race['build_place']][warehouse['name'].index(place)]
        else:
            # 从一个地方到另一个地方
            dis += station[] 
        stations[name]

def mkFounder(data):
    race = {}
    wareh = data['warehouse']
    init_wareh = 0
    
    race['build_place'] = wareh['name'][init_wared]
    race['build_cose'] = wareh[race['build_place']]['cost']
    race['transport_cost'] = raceTcost(race, data['station'], data['warehouse'])
    return race

def multiply(race, w):
    return race

def selection(race):
    return race

def evaluate(idealRace, race, w):
    ideal_w = idealRace['build_cost'] + idealRace['transport_cost'] + idealRace['time_cost']
    if ideal_w < w:
        w = ideal_w
        race = ideal_race
    return w, race

def integrate(race):
    w = race['build_cost'] + race['transport_cost'] + race['time_cost']
    mapData = {} # 作图使用数据
    return w, mapData

def geneticOptimize(data):
    w = 0
    mapData = {}
    race = mkFounder(data)
    gene = 0
    max_race = race
    while gene < times:
        race = multiply(race, w)
        idealRace = selection(race)
        w, race = evaluate(idealRace, race, w)
        gene += 1
    w, mapData = integrate(max_race)
    return w, mapData

if __name__ == "__main__":
    data = initData()
    w, mapData = geneticOptimize(data)
    print(w)
    drawMap(mapData)

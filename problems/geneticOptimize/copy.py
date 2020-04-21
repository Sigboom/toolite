#!/usr/bin/env python
# coding=utf-8
tsp_data = {
"需求点" : "0-15 的需求点分别对应：金山,奉贤,南通,常州,淮安,泰州,扬州,盐城,连云港,徐州,芜湖, 蚌埠,嘉兴,绍兴,台州,温州",
"IND_C" : [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15],
"需求点的送货量" : "件",
"D_I" : [2890,1800,1500,2000,1000,500,700,1200,1400,1100,600,1250,1820,2200,800,2500],
"需求点的取货量" : "件",
"P_I" : [2500,1200,3000,2100,800,400,400,950,750,1600,2550,900,1700,1650,2100,2790],
"选址点" : "7 个选址点分别对应：杭州,南京,苏州,浦东,合肥,宁波,义乌",
"IND_M" : [16,17,18,19,20,21,22],
"选址点建设成本" : "万元",
"Cost_M" : [900,800,900,1000,550,750,600],
"选址点仓库容量" : "件",
"C_M" : [50000,50000,50000,50000,50000,50000,50000],
"车厢容量" : "件",
"Q_K" : 5000,
"车辆最大行驶距离" : "公里",
"L_K" : 1000,
"单位公里行驶费" : "元/公里",
"C_ij" : 1.5,
"最大迭代次数" : "次",
"Max_Gen" : 1000,
"个体长度" :"需求点[0-15] + 选址点[16-22]",
"IND_Size" : 23,
"种群大小" : "",
"Population_Size" : 100,
"交叉概率" : "",
"Cxpb" : 0.7,
"变异概率" : "",
"Mutpb" : 0.2,
"需求点间的距离" : "16*16",
"Distance_CC" :
[
[0,29,182,215,451,282,323,374,554,642,364,519,67,129,316,399],
[29,0,160,205,433,264,304,339,508,623,373,510,80,169,342,428],
[182,160,0,138,295,126,166,189,357,485,331,399,172,276,452,534],
[215,205,138,0,271,102,114,212,373,445,202,316,172,263,452,505],
[451,433,295,271,0,190,178,127,127,198,292,242,404,508,681,762],
[282,264,126,102,190,0,70,122,291,379,274,309,235,336,515,598],
[323,304,166,114,178,70,0,169,276,341,212,247,271,357,551,600],
[374,339,189,212,127,122,169,0,198,324,378,354,327,431,607,689],
[554,508,357,373,127,291,276,198,0,214,424,351,517,621,797,873],
[642,623,485,445,198,379,341,324,214,0,411,183,593,670,873,913],
[364,373,331,202,292,274,212,378,424,411,0,240,286,334,549,563],
[519,510,399,316,242,309,247,354,351,183,240,0,473,537,747,777],
[67,80,172,172,404,235,271,327,517,593,286,473,0,366,287,366],
[129,169,276,263,508,336,357,431,621,670,334,537,366,0,222,270],
[316,342,452,452,681,515,551,607,797,873,549,747,287,222,0,132],
[399,428,534,505,762,598,600,689,873,913,563,777,366,270,132,0]
],
"选址点与需求点间的距离" : "7*16",
"Distance_MC" :
[
[130,160,250,200,450,310,300,400,600,600,270,500,90,70,280,300],
[350,340,250,140,200,170,100,270,330,340,100,200,280,340,550,580],
[130,120,110,100,340,170,200,260,450,530,150,400,70,180,350,450],
[75,50,140,200,410,250,280,320,500,600,380,500,110,210,400,470],
[500,490,400,300,330,320,250,420,460,330,150,150,430,480,680,700],
[150,180,300,310,550,380,400,470,700,740,430,630,150,110,180,270],
[240,270,360,340,600,430,450,500,730,750,400,700,200,120,180,200]
]
}
# -*- coding: utf-8 -*-
# @Time : 2018/3/27 1:52
# @Author : cap
# @FileName: tao_tsp.py
# @Software: PyCharm Community Edition
import random, os
import json
# 导入相关数据，
tsp = tsp_data

IND_SIZE = tsp['IND_Size']
IND_C = tsp['IND_C']
D_I = tsp['D_I']
P_I = tsp['P_I']
IND_M = tsp['IND_M']
Cost_M = tsp['Cost_M']
C_M = tsp['C_M']
Q_K = tsp['Q_K']
L_K = tsp['L_K']
C_ij = tsp['C_ij']
Distance_CC = tsp['Distance_CC']
Distance_MC = tsp['Distance_MC']
Max_Gen = tsp['Max_Gen']
Population_Size = tsp['Population_Size']
Cxpb = tsp['Cxpb']
Mutpb = tsp['Mutpb']

# 制定编码规则，个体编码最后一个数必须是选址点
def sample_ind(IND_SIZE):
    temp = [99999999, 8888888]
    while temp[-1] not in IND_M:
        temp = random.sample(range(IND_SIZE), IND_SIZE)
    return temp

# 计算路径的总距离
def distance_tsp(arr):
    # arr 格式为[选址点，需求点⋯⋯需求点，选址点]
    distance = Distance_MC[arr[0]-len(IND_C)][arr[1]] + Distance_MC[arr[-1]-len(IND_C)][arr[-2]]
    if len(arr) > 3:
        for gene1, gene2 in zip(arr[1:-2], arr[2:-1]):
            distance += Distance_CC[gene1][gene2]
    return distance

# 路线划分
def indSplit(individual):
    # 按照选址点，对个体进行分割
    site = {}
    temp = []
    for i in individual:
        if i in IND_M:
            temp.append(i)
            temp.insert(0, i)
            site[i] = temp
            temp = []
        else:
            temp.append(i)
        
    # 删除无效的选址点
    site_pop = []
    for i in site.keys():
        if len(site.get(i)) == 2:
            site_pop.append(i)
    for i in site_pop:
        site.pop(i)
    return site

# 目标函数
def evalTSP(individual):
    site = indSplit(individual)
    # 计算成本
    cost = 0
    for i in site.keys():
        distance = distance_tsp(site.get(i))
        # 车辆最大行驶里程约束条件
        if distance >= L_K:
            distance = 99999999
        # 车载量约束条件
        # 1、车辆从选址点出来时的初始车载量
        C_0 = 0
        temp_list = site.get(i)
        temp_arr = [m for m in temp_list[1:-1]]
        for j in temp_arr:
            C_0 += D_I[j]
        if C_0 > Q_K:
            distance = 99999999
        # 2、运输中的车载量约束条件
        for k in temp_arr:
            C_0 = C_0 - D_I[k] + P_I[k]
            if C_0 > Q_K:
                distance = 99999999
        cost += Cost_M[i-len(IND_C)] * 10000 + C_ij * distance
    return round(cost)

# 竞争选择，依据 fitness 最大
def selRandom(individuals, k):
    return [random.choice(individuals) for i in range(k)]

def selTournament(individuals, k, tournsize=3):
    # individuals：候选池
    # k:选择的个数
    # tournsize：竞争个数
    chosen = []
    for i in range(k):
        aspirants = selRandom(individuals, tournsize)
        temp = []
        for j in range(len(aspirants)):
            temp.append(aspirants[j][-1])
        chosen.append(aspirants[temp.index(max(temp))])
    return chosen

# 采用部分匹配交叉
def cxPartialyMatched(ind1, ind2):
    ind1, ind2 = ind1[:IND_SIZE], ind2[:IND_SIZE]
    size = min(len(ind1), len(ind2))
    p1, p2 = [0] * size, [0] * size
    for i in range(size):
        p1[ind1[i]] = i
        p2[ind2[i]] = i
    cxpoint1 = random.randint(0, size)
    cxpoint2 = random.randint(0, size - 1)
    if cxpoint2 >= cxpoint1:
        cxpoint2 += 1
    else:
        cxpoint1, cxpoint2 = cxpoint2, cxpoint1
    for i in range(cxpoint1, cxpoint2):
        temp1 = ind1[i]
        temp2 = ind2[i]
        ind1[i], ind1[p1[temp2]] = temp2, temp1
        ind2[i], ind2[p2[temp1]] = temp1, temp2
        p1[temp1], p1[temp2] = p1[temp2], p1[temp1]
        p2[temp1], p2[temp2] = p2[temp2], p2[temp1]
    fitness1, fitness2 = -evalTSP(ind1), -evalTSP(ind2)
    ind1.append(fitness1)
    ind2.append(fitness2)
    return ind1, ind2

# 变异规则
def mutShuffleIndexes(individual, indpb=0.05):
    individual = individual[:IND_SIZE]
    size = len(individual)
    for i in range(size):
        if random.random() < indpb:
            swap_indx = random.randint(0, size - 2)
            if swap_indx >= i:
                swap_indx += 1
            individual[i], individual[swap_indx] = individual[swap_indx], individual[i]
    fitness = -evalTSP(individual)
    individual.append(fitness)
    return individual

# 交叉、变异
def varAnd(population, cxpb, mutpb):
    offspring = population if population else []
    for i in range(1, len(offspring), 2):
        if random.random() < cxpb:
            offspring[i - 1], offspring[i] = cxPartialyMatched(offspring[i - 1], offspring[i])
            if offspring[i - 1][-2] not in IND_M:
                offspring[i - 1] = sample_ind(IND_SIZE)
                fitness = -evalTSP(offspring[i - 1])
                offspring[i - 1].append(fitness)
            if offspring[i][-2] not in IND_M:
                offspring[i] = sample_ind(IND_SIZE)
                fitness = -evalTSP(offspring[i])
                offspring[i].append(fitness)
        for i in range(len(offspring)):
            if random.random() < mutpb:
                offspring[i] = mutShuffleIndexes(offspring[i])
                if offspring[i][-2] not in IND_M:
                    offspring[i] = sample_ind(IND_SIZE)
                    fitness = -evalTSP(offspring[i])
                    offspring[i].append(fitness)
    return offspring

# 主函数
def main():
    # random.seed(300)
    # 初始化种群，计算适应度值并将适应度值添加到个体最后
    pop = []
    for i in range(Population_Size):
        individual = sample_ind(IND_SIZE)
        fitness = -evalTSP(individual)
        individual.append(fitness)
        pop.append(individual)
    
    Best = []
    for gen in range(1, Max_Gen+1):
        offspring = selTournament(pop, len(pop))
        offspring = varAnd(offspring, Cxpb, Mutpb)
    
        temp = []
        for i in range(len(offspring)):
            temp.append(offspring[i][-1])
        best_ind = [ind for ind in offspring[temp.index(max(temp))]]
        print('第%d 代的最佳个体为：' % gen, best_ind)
        pop[:] = offspring
        while gen == Max_Gen:
            Best = [ind for ind in best_ind]
            gen += 1
        best_ind = []
    print('\n\n')
    print('最佳划分方案为：')
    site = indSplit(Best[0:IND_SIZE])
    for i in site.keys():
        print('选址点：', i, ' 需求点：', site.get(i))
    print('年总成本为：', -Best[-1]/1000, '万元')

if __name__ == "__main__":
    main()
    os.system("pause")

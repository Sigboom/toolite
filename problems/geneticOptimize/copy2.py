#!/usr/bin/env python
# coding=utf-8

import os
import random
import json

tsp_data = {
"需求点" : "0-9 的需求点分别对应：开封,商丘,周口,南阳,焦作,荆州,宜昌,漯河,孝感,麻城",
"IND_C" : [0,1,2,3,4,5,6,7,8,9],
"需求点的送货量" : "件",
"D_I" : [2000,1500,600,1300,1250,1350,500,900,700,800],
"需求点的取货量" : "件",
"P_I" : [1600,1300,500,1500,900,1000,600,700,400,1000],
"选址点" : "3 个选址点分别对应：郑州，信阳，武汉",
"IND_M" : [10,11,12],
"选址点建设成本" : "万元",
"Cost_M" : [900,700,1000],
"选址点仓库容量" : "件",
"C_M" : [30000,30000,30000],
"车厢容量" : "件",
"Q_K" : 5000,
"车辆最大行驶距离" : "公里",
"L_K" : 800,
"单位公里行驶费" : "元/公里",
"C_ij" : 2,
"最大迭代次数" : "次",
"Max_Gen" : 1000,
"个体长度" :"需求点[0-9] + 选址点[10-12]",
"IND_Size" : 13,
"种群大小" : "",
"Population_Size" : 100,
"交叉概率" : "",
"Cxpb" : 0.7,
"变异概率" : "",
"Mutpb" : 0.2,
"需求点间的距离" : "10*10",
"Distance_CC" :
[
[0,146,152,307,144,628,670,179,498,439],
[146,0,140,372,275,692,735,202,496,433],
[152,140,0,237,268,557,600,62,361,308],
[307,372,237,0,329,334,376,175,343,389],
[144,275,268,329,0,657,699,229,555,578],
[628,692,557,334,657,0,152,501,209,328],
[670,735,600,376,699,152,0,546,298,422],
[179,202,62,175,229,501,546,0,330,355],
[498,496,361,343,555,209,298,330,0,129],
[439,433,308,389,578,328,422,355,129,0]
],
"选址点与需求点间的距离" : "3*10",
"Distance_MC" :
[
[78,200,168,257,86,561,633,145,469,492],
[353,349,205,186,400,332,400,174,170,180],
[525,520,365,368,597,223,317,372,76,112]
]
}
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
    os.system("pause");


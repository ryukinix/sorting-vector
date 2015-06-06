# -*- coding:utf-8 -*-
#autor -> manoel vilela
#gerando graficos em relação a eficiencia dos algoritmos de ordenação bubble, merge and personal

import pylab



def extract_data(file_name):
	data = open(file_name, "r").read().split()
	data = [element.split() for element in data.split("=")]
	vector, values = data
	

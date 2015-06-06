#! /usr/bin/env python2
# -*- coding:utf-8 -*-

#plot_program
import pylab
from numpy import sin
from random import choice
colors = 'bgrcmykx'
plots = 0

def plot(func, label1, label2, color = colors):
	global plots
	pylab.figure(plots)
	
	# função usada como exemplo
	# pylab.arange(inicio, fim, passo) - define um 'arranjo' com os valores de entrada.
	entrada = pylab.arange(-n, n, 0.1)

	# saida - recebe um 'arranjo' com os resultados da
	# função sobre cada ítem de 'entrada'.
	saida = func(entrada)

	# pylab.plot(e, s) - 'plota' os dados de entrada e saída
	# no grafico.
	pylab.plot(entrada, saida, choice(colors), antialiased = True)

	# pylab.xlabel(s) - define o label do eixo x.
	pylab.xlabel(label1)

	# pylab.ylabel(s) - define o label do eixo y.
	pylab.ylabel(label2)

	# pylab.title(s) - define o titulo do grafico.
	pylab.title('Wave function')

	# pylab.grid(boleano) - define se exibirá ou não as 'grids'
	# no gráfico.
	pylab.grid(True)

	plots += 1	

	
	


#y = ym * sin(kx +- wt + phi)

def wave_t(t):
	return ym * sin(-w*t + phi)
def wave_x(x):
	return ym * sin(k*x + phi)

ym = float(input('Amplitude: '))
w = float(input('Frequencia angular: '))
phi = float(input('Constante de fase: '))
k = float(input('Número de ondas: '))
n = float(input('Faixa de campo para analise: '))

plot(wave_t, 'Segundos(t)', 'Metro(y)', colors[3:])
plot(wave_x, 'Metros(x)', 'Metros(y)', colors[:3])

# pylab.show() - exibe o gráfico
pylab.show()
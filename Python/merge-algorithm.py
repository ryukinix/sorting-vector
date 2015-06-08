def merge(lista_x,lista_y):
  if lista_x == []:
       return lista_y
  elif lista_y == []:
       return lista_x
  else:
      if lista_x[0] < lista_y[0]:
          return [lista_x[0]] + merge(lista_x[1:],lista_y)
      else:
          return [lista_y[0]] + merge(lista_x,lista_y[1:])
 
def mergesort(lista):
  if len(lista) <= 1:
     return lista
  else:
      mid = len(lista) // 2
      return merge(mergesort(lista[:mid]), mergesort(lista[mid:]))

print(mergesort([1, 4, 5, 6, 7, 3, 8]))
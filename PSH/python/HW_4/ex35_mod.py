"""
내가 직접 만든 모듈
"""
from functools import * # *(asterisk)를 붙이면 functools 안의 모든 함수를 불러 사용하겠다는 뜻

"""
reduce(집계함수, 순회가능한 데이터, [initializer = None])      #functools 모듈내의 함수
첫번째 파라미터 : 함수 or 람다, 2개의 인자를 받아야 함(첫번째 : 누적자, 두번째 : 현재값)
				  -누적자 : 함수 실행의 시작부터 끝까지 계속해서 재사용되는 값
				  -현재값 : 루프 돌면서 계속해서 바뀌는 값
두번째 파라미터 : 계산하고자 하는 list
세번째 파라미터 : 생략가능, 
"""
def intersect(*ar):
	return reduce(__intersectSC, ar)

def __intersectSC(listX, listY):
	setList = []
	for x in listX:
		if x in listY:
			setList.append(x)
	return setList

def difference(*ar):
	setList = []
	intersectSet = intersect(*ar)
	unionSet = union(*ar)
	for x in unionSet:
		if not x in intersectSet:
			setList.append(x)
	return setList

def union(*ar):
	setList = []
	for item in ar:
		for x in item:
			if not x in setList:
				setList.append(x)
	return setList

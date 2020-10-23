class person:
    def __init__(self,name,age,address):
        self.hello = '안녕하세요'
        self.name = name
        self.age = age
        self.address =address
        self.__wallet = 10000 #비공개 클래스 Private class내부에서만 호출 가능
        self.health = 20

    def hi(self):
        print('{0}저는 {1}입니다'.format(self.hello,self.name))

    def status_wallet(self):
        print('지갑에 {0}원의 돈이 잇습니다'.format(self.__wallet))

    def __status_secret(self):
        print('사실 36살입니다')

    def put_status(self,HP):
        self.health=HP

class Person:
    count = 0    # 클래스 속성
 
    def __init__(self):
        Person.count += 1    # 인스턴스가 만들어질 때
                             # 클래스 속성 count에 1을 더함
 
    @classmethod
    def print_count(cls):
        print('{0}명 생성되었습니다.'.format(cls.count))    # cls로 클래스 속성에 접근

        
kks = person('강경수',25,'서울연희동')
print('이름:',kks.age)
print('나이:',kks.address)
kks.status_wallet()

kks.age = 10
kks.put_status(30)


man1 = Person()
man2 = Person()
 
Person.print_count()    # 2명 생성되었습니다.

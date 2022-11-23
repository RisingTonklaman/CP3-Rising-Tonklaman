import json
file=open('JS0N.JSON','r')
k=file.read()
print(k)
print('--------------------')
def readJson():
    # ข้อมูล JSON ที่เราต้องการอ่าน
    x =  '{ "name":"John", "age":30, "city":"New York"}'
    # แปลงข้อมูลให้กลายเป็นรูปที่เราสามารถใช้ได้
    y = json.loads(x)
    # ทำการเรียกข้อมูล age ออกมาแสดง
    print(y["age"])

def writeJson(file):
    # สร้างข้อมูลที่เราต้องการแปลง(ประเภท dictionary)
    x = {
        "name": "John",
        "age": 30,
        "city": "New York"
    }
    # คำสั่งที่ใช้ในการแปลง
    y = json.dumps(x)
    z = json.loads(k)
    # มาลองดูผลลัพธ์กัน
    print(x)
    print(y)
    print(z)
#readJson()
writeJson(file)
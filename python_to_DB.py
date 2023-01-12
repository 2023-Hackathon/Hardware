# import pymysql
#
# def get_db():
#     try:
#         db = pymysql.connect(host='125.184.79.99', port=3306, user='root', passwd='Haley0123.', db='BSSM_DB', charset='utf8')
#         cursor = db.cursor()
#         return db, cursor
#     except Exception as e:
#         print(e)
#         return False, False
#
# db, cursor = get_db()
#
# if db == False:
#     print('MySQL Connect Error')
#
# try:
#     cursor.execute("INSERT INTO sensor2 (value1, value2) VALUES (0, 3)")
#     db.commit()
#     print('Data Add True')
# except Exception as e:
#     print(e)



import pymysql

def get_db():
    try:
        db = pymysql.connect(host='192.168.230.208', port=3306, user='simUser2', passwd='Timaudgy&7', db='db', charset='utf8')
        cursor = db.cursor()
        return db, cursor
    except Exception as e:
        print(e)
        return False, False

db, cursor = get_db()

if db == False:
    print('MySQL Connect Error')

try:
    cursor.execute("INSERT INTO sensor2 (value1, value2) VALUES (9, 9)")
    db.commit()
    print('Data Add True')
except Exception as e:
    print(e)
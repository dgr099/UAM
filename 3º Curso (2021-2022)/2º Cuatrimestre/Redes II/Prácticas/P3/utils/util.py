from re import S


def isIPv4(s):
    try:
        return str(int(s)) == s and 0 <= int(s) <= 255
    except:
        return False

def isIPv6(s):
    if len(s) > 4:
        return False
    try:
        return int(s, 16) >= 0 and s[0] != '-'
    except:
        return False

def checker(str_to_check, type):
    if type == 'IP':
        if str_to_check.count(".") == 3 and all(isIPv4(i) for i in str_to_check.split(".")):
            return True
        if str_to_check.count(":") == 7 and all(isIPv6(i) for i in str_to_check.split(":")):
            return True
        return False
    if type == 'PORT':
        if 0 <= int(str_to_check) <= 65535:
            return True
        return False
    if type == 'PROTOCOL':
        try:
            return str(int(str_to_check)) == str_to_check
        except: 
            return False
    return False
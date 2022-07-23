import sys, argparse

def required_length(nmin,nmax):
    class RequiredLength(argparse.Action):
        def __call__(self, parser, args, values, option_string=None):
            if not nmin<=len(values)<=nmax:
                print('ERROR: numero de argumentos para --create_id incorrecto')
                print('Sintaxis: python securebox_client.py --create_id [nombre] [email] [Optional: alias]')
                sys.exit()
            setattr(args, self.dest, values)
    return RequiredLength

def none_string_check(string):
    if string:
        return str(string)
    return "None"

def check(r, function_name):
    if r.status_code > 299 or r.status_code < 200:
        print("Error en " + function_name + " status code: " + str(r.status_code))
        print(r.json()['description'])
        sys.exit()
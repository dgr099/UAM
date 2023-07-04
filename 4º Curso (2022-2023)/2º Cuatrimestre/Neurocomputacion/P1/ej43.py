import subprocess
import sys
#perceptron -m 4 -f ./data/and.txt -e 20 -a 0.1 -u 0.5
n_epocas = 20
def range_with_floats(start, stop, step):
    while stop > start:
        yield start
        start += step
cmd_str = "chmod +x ./exe/perceptron"
subprocess.run(cmd_str, shell=True)

b_accurate=0.0
b_a=0.1
b_u=0.1
b_t=0.1
res=""
path_files = "predicciones/"
file_perc = "ej_4.3_perceptron.txt"
file_adaline = "ej_4.3_adaline.txt"
#probamos cual es la mejor combinación de parámetros
print("Checking parameters perceptron...")
for tol in range_with_floats(0.1, 5, 0.5):
    for u in range_with_floats(0.1, 5, 0.5):
        for a in range_with_floats(0.1, 5, 0.5):
            cmd_str = "./exe/perceptron -m 2 -f ./data/problema_real2.txt -f ./data/problema_real2_no_etiquetados.txt -e 40 -a " + str(a)  + " -t "  + str(tol) + " -u " +str(u)
            with subprocess.Popen(cmd_str, shell=True, bufsize=1, universal_newlines=True, stdout=subprocess.PIPE) as p:
                
                (output, err) = p.communicate()
                exit_code = p.wait()
                #print(output)
                accurate = float(output[10:17])
                accurate=1.0
                if(accurate>b_accurate):
                    b_a = a
                    b_t = tol
                    b_u = u
    #una vez con la mejor combinación mostramos pesos y predicciones
            
cmd_str = "./exe/perceptron -m 3 -f ./data/problema_real2.txt -f ./data/problema_real2_no_etiquetados.txt -e 40 -a " + str(b_a)  + " -t "  + str(b_t) + " -u " +str(b_u)
print("saving results perceptron")
with subprocess.Popen(cmd_str, shell=True, bufsize=1, universal_newlines=True, stdout=subprocess.PIPE) as p:
    (output, err) = p.communicate()
    exit_code = p.wait()
    f = open(path_files + file_perc, "w")
    f.write("Parameters: "+ "-a " + str(b_a)  + " -t "  + str(b_t) + " -u " +str(b_u) + "\n\nPesos:" + output[17:])
    f.close()

print("Checking parameters adaline...")
for tol in range_with_floats(0.1, 5, 0.5):
    for u in range_with_floats(0.1, 5, 0.5):
        for a in range_with_floats(0.1, 5, 0.5):
            cmd_str = "./exe/adaline -m 2 -f ./data/problema_real2.txt -f ./data/problema_real2_no_etiquetados.txt -e 40 -a " + str(a)  + " -t "  + str(tol) + " -u " +str(u)
            with subprocess.Popen(cmd_str, shell=True, bufsize=1, universal_newlines=True, stdout=subprocess.PIPE) as p:
                
                (output, err) = p.communicate()
                exit_code = p.wait()
                #print(output)
                accurate = float(output[10:17])
                accurate=1.0
                if(accurate>b_accurate):
                    b_a = a
                    b_t = tol
                    b_u = u
    #una vez con la mejor combinación mostramos pesos y predicciones
            
cmd_str = "./exe/adaline -m 3 -f ./data/problema_real2.txt -f ./data/problema_real2_no_etiquetados.txt -e 40 -a " + str(b_a)  + " -t "  + str(b_t) + " -u " +str(b_u)
print("saving results adaline")
with subprocess.Popen(cmd_str, shell=True, bufsize=1, universal_newlines=True, stdout=subprocess.PIPE) as p:
    (output, err) = p.communicate()
    exit_code = p.wait()
    f = open(path_files + file_adaline, "w")
    f.write("Parameters: "+ "-a " + str(b_a)  + " -t "  + str(b_t) + " -u " +str(b_u) + "\n\nPesos:" + output[17:])
    f.close()


sys.exit()


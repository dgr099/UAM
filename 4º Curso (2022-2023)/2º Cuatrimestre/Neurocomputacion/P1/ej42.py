import subprocess
import matplotlib as plt

def ejecuta_comando(comando):
    with subprocess.Popen(comando, shell=True,  bufsize=1, universal_newlines=True, stdout=subprocess.PIPE) as p:
        (output, _) = p.communicate()
        p.wait()
        return output.split()[2]

umbrales = [umbral/10 for umbral in range(1, 101)]
alphas = [alpha/10 for alpha in range(1, 11)]
tolerancias = [tolerancia/10 for tolerancia in range(1, 11)]
num_epocas = [epoca for epoca in range(10, 101, 5)]
porcentaje_train = 0.7

umbral_cte = 0.5
alpha_cte = 0.2
tolerancia_cte = 0.1
epocas_cte = 100

ruta_datos = "./data/problema_real1.txt"
ruta_exe = "./exe/"
ruta_resultados = "./predicciones/"

# Bucle para epocas
with open(ruta_resultados + "epocas.txt", "w") as f:
    for epocas in num_epocas:
        print(epocas)
        comando = ruta_exe + "adaline" + " -m 1 -f " + ruta_datos + " -p " + str(porcentaje_train) + \
            " -e " + str(epocas) + " -t 0.1 -a 0.2 -u 0.5"
        accurate_ada = ejecuta_comando(comando)
        comando = ruta_exe + "perceptron" + " -m 1 -f " + ruta_datos + " -p " + str(porcentaje_train) + \
            " -e " + str(epocas) + " -t 0.1 -a 0.2 -u 0.5"
        accurate_per = ejecuta_comando(comando)
        f.write(str(epocas) + " " + str(accurate_ada) + " " + str(accurate_per) + "\n")

# Bucle para tolerancias
with open(ruta_resultados + "tolerancias.txt", "w") as f:
    for tolerancia in tolerancias:
        print(tolerancia)
        comando = ruta_exe + "adaline" + " -m 1 -f " + ruta_datos + " -p " + str(porcentaje_train) + \
            " -e 100 -t " + str(tolerancia) + " -a 0.2 -u 0.5"
        accurate_ada = ejecuta_comando(comando)
        comando = ruta_exe + "perceptron" + " -m 1 -f " + ruta_datos + " -p " + str(porcentaje_train) + \
            " -e 100 -t " + str(tolerancia) + " -a 0.2 -u 0.5"
        accurate_per = ejecuta_comando(comando)
        f.write(str(tolerancia) + " " + str(accurate_ada) + " " + str(accurate_per) + "\n")


# Bucle para constantes de aprendizaje
with open(ruta_resultados + "alphas.txt", "w") as f:
    for alpha in alphas:
        print(alpha)
        comando = ruta_exe + "adaline" + " -m 1 -f " + ruta_datos + " -p " + str(porcentaje_train) + \
            " -e 100 -t 0.1 -a " + str(alpha) + " -u 0.5"
        accurate_ada = ejecuta_comando(comando)
        comando = ruta_exe + "perceptron" + " -m 1 -f " + ruta_datos + " -p " + str(porcentaje_train) + \
            " -e 100 -t 0.1 -a " + str(alpha) + " -u 0.5"
        accurate_per = ejecuta_comando(comando)
        f.write(str(alpha) + " " + str(accurate_ada) + " " + str(accurate_per) + "\n")


# Bucle para umbrales
with open(ruta_resultados + "umbrales.txt", "w") as f:
    for umbral in umbrales:
        print(umbral)
        comando = ruta_exe + "adaline" + " -m 1 -f " + ruta_datos + " -p " + str(porcentaje_train) + \
            " -e 100 -t 0.1 -a 0.2 -u " + str(umbral)
        accurate_ada = ejecuta_comando(comando)
        comando = ruta_exe + "perceptron" + " -m 1 -f " + ruta_datos + " -p " + str(porcentaje_train) + \
            " -e 100 -t 0.1 -a 0.2 -u " + str(umbral)
        accurate_per = ejecuta_comando(comando)
        f.write(str(umbral) + " " + str(accurate_ada) + " " + str(accurate_per) + "\n")
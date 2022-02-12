from selenium import webdriver
import time, requests
import database
import os

def search_google(search_query, type):
    try:
        path = ""
        if(type==1):
            aux = search_query.split(",")
            search_url = f"https://www.google.com/search?site=&tbm=isch&source=hp&biw=1873&bih=990&q=" + aux[1] + " " + aux[0] + " actor" + " imagesize:200x200"
            path = "static/images/actors/"
        else:
            search_url = f"https://www.google.com/search?site=&tbm=isch&source=hp&biw=1873&bih=990&q=" + search_query + " imagesize:800x1200"
            path = "static/images/posters/"
        browser.get(search_url)
        elements = browser.find_elements_by_class_name('rg_i')
        count_2=0
        reponse = None
        for e in elements:
            e.click()
            time.sleep(1.25)
            element = browser.find_elements_by_class_name('v4dQwb')
            if count_2 == 0:
                big_img = element[0].find_element_by_class_name('n3VNCb')
            else :
                big_img = element[1].find_element_by_class_name('n3VNCb')

            # write image to file
            try:
                reponse = requests.get(big_img.get_attribute("src"))
                if(reponse.status_code == 200):
                    break
            except:
                count_2+=1
        if reponse is not None and reponse.status_code == 200:
            with open(path + search_query + ".jpg","wb") as file:
                file.write(reponse.content)
    except:
        return

browser = webdriver.Chrome()
count = 0
movies = database.db_listOfMovies()
for movie in movies:
    search_query = movie.movietitle
    search_query = search_query.replace("/", "-")
    ulr = 'static/images/posters/'  + search_query +".jpg"
    if(os.path.isfile(ulr)):
        continue
    search_google(search_query, 0)
    count += 1
print("Películas: se han guardado: " + str(count) + "/" + str(len(movies)))
count = 0
actors = database.db_listOfActors()
for actor in actors:
    search_query = actor.actorname
    search_query = search_query.replace("/", "-")
    ulr = 'static/images/actors/'  + search_query +".jpg"
    if(os.path.isfile(ulr)):
        continue
    search_google(search_query, 1)
    count += 1
print("Actores: se han guardado: " + str(count) + "/" + str(len(actors)))
browser.close()

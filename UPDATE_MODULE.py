#You can read mor on github website: https://github.com/wleng2001/UPM-UPdate_Module_for_app
#check and install update
#import-------------------------
from datetime import datetime
from github import Github
#from git import Repo
import git
from os import getcwd
import requests
#variables----------------------
last_update="2022-10-19"
repo_name="UPM-UPdate_Module_for_app"
url="https://raw.rawgit.net/wleng2001/UPM-UPdate_Module_for_app/main/UPDATE_MODULE.py"
new_version_name="UPDATE_MODULE.py"
#update check-------------------
def update_check(last_update, repo_name):
    last_date=datetime.fromisoformat(last_update)
    g=Github()
    try:
        for i in g.search_repositories(repo_name):
            repo=i
        date=repo.pushed_at
        if date.date()==last_date.date():
            return False
        else:
            return True
    except:
        return None
#download update
def download_update_repo(url, path):
    try:
        git.Git(path).clone(url)
        return True
    except:        
        return False

def download_update_file(url, path, file_name): #url must be in raw format for example from rawgit.net website
    try:
        file=requests.get(url)
        file=file.content
        open(file_name,'wb').write(file)
        return True
    except:
        return False
    
def update_self():
    update_available=update_check(last_update, repo_name)
    if update_available==None:
        print("You don't have internet connection.")
    elif update_available==True:
        print("Update of update module is available!")
        ask=input("Do you want download it now (Y/n): ")
        ask=ask.upper()
        if_download=None
        if ask=="Y":
            if_download=download_update_file(url,getcwd(), new_version_name)
        if if_download==False:
            print("Lost connection file wasn't downloaded")
    else:
        print("App is current")



import os
import requests
import zipfile
import subprocess
import sys
import shutil

need_environment_moved = False

# Vérifier si tqdm est installé, sinon l'installer
try:
    from tqdm import tqdm
except ImportError:
    print("Dépendances non détectée : Installation de tqdm")
    os.system('pip install tqdm')
    from tqdm import tqdm
    need_environment_moved = True


try:
    import mediapipe
except ImportError:
    print("Dépendances non détectée : Installation de mediapipe")
    os.system('pip install mediapipe')
    import mediapipe
    need_environment_moved = True

if(need_environment_moved):
    src_folder = sys.prefix
    dst_folder = '../packages/Python310'
    shutil.copytree(src_folder, dst_folder)
    print('Python310 folder has been copied successfully.')

class FileDownloader:
    def __init__(self, urls, filenames, destination_folder, opencv_dir, opencv_url):
        self.urls = urls
        self.filenames = filenames
        self.destination_folder = destination_folder
        self.opencv_dir = opencv_dir
        self.opencv_url = opencv_url


    def downloadOpenCV(self):

        print ("Install opencv .Exe")
        # Create the destination folder if it doesn't exist
        if not os.path.exists(os.path.join(self.destination_folder,self.opencv_dir)):
            # Download the OpenCV installer
            filename = os.path.join(self.destination_folder, 'opencv_installer.exe')
            response = requests.get(self.opencv_url )
            with open(filename, 'wb') as f:
                f.write(response.content)

            # Launch the OpenCV installer
            print("Launch executable opencv")
            opencv_install_path = os.path.join(self.destination_folder, 'opencv-4.7.0')
            subprocess.run([filename, '/verysilent'])
            print("Opencv is now installed")
            os.remove(filename)
            

        



    def download(self):
        for index in range(len(self.filenames)):
            print ("===================================================")
            # Vérifier si le fichier existe déjà
            url = self.urls[index]
            filename = self.filenames[index]
            if os.path.exists(os.path.join(self.destination_folder, filename)):
                print('Le fichier {} existe déjà dans le dossier de destination. Aucun téléchargement nécessaire.'.format(filename))
                continue

            # Télécharger le fichier avec une barre de progression
            response = requests.get(url, stream=True)
            total_size_in_bytes = int(response.headers.get('content-length', 0))
            block_size = 1024
            print("Téléchargement du fichier {}".format(filename))
            progress_bar = tqdm(total=total_size_in_bytes, unit='iB', unit_scale=True)
            with open(os.path.join(self.destination_folder, filename+".zip"), 'wb') as file:
                for data in response.iter_content(block_size):
                    progress_bar.update(len(data))
                    file.write(data)
            progress_bar.close()
            print("Extraction du fichier {}".format(filename))
            self.extract_zip(filename)


    def extract_zip(self,filename):
        # Vérifier si le fichier zip existe déjà
        zip_path = os.path.join(self.destination_folder, filename+".zip")
        if not os.path.exists(zip_path):
            print('Le fichier {} n\'existe pas dans le dossier de destination. Aucune extraction possible.'.format(filename))
            return

        # Extraire le contenu du fichier zip
        with zipfile.ZipFile(zip_path, 'r') as zip_ref:
            zip_ref.extractall(self.destination_folder)

        # Supprimer le fichier zip après extraction
        os.remove(zip_path)
        print("Téléchargement du fichier {} terminé".format(filename))


# Télécharger et extraire le fichier zip OpenCV 4.7.0
urls = [
       'https://boostorg.jfrog.io/artifactory/main/release/1.81.0/source/boost_1_81_0.zip',
       'https://github.com/pybind/pybind11/archive/refs/tags/v2.10.4.zip']

opencv_url = 'https://github.com/opencv/opencv/releases/download/4.7.0/opencv-4.7.0-windows.exe'
opencv_dir = 'opencv-4.7.0'
filenames = [
             'boost_1_81_0',
             'pybind11-2.10.4'
             ]
destination_folder = '../packages/'

downloader = FileDownloader(urls, filenames, destination_folder,opencv_dir,opencv_url)
downloader.download()
downloader.downloadOpenCV()




# Projet_RDV_Salhi_Abdelaziz

## Description 

#### Premiere etape 
Nous avons commencé le projet par faire le render d'une simple image comme debut [first out image](https://github.com/RidaMohamed/Projet_RDV_Salhi_Abdelaziz/blob/master/out/out_first.png),
par la suite nous avons fait le lines drawing et traingles pour tester suivant l'algo " bresenham algorithm " limage out est [second out image](https://github.com/RidaMohamed/Projet_RDV_Salhi_Abdelaziz/blob/master/out/out_second.png)

#### Deuxieme etape 
Pour faire le premier affichage du monstre nous avon utiliser la mehode orthographic projection pour l'affichage de mesh du modele [fourth out image](https://github.com/RidaMohamed/Projet_RDV_Salhi_Abdelaziz/blob/master/out/out_fourth.png),
apres nous avons afficher le mesh du monstre avec algorithme de barycentric coordinates [fifth out image](https://github.com/RidaMohamed/Projet_RDV_Salhi_Abdelaziz/blob/master/out/out_fifth.png),ensuite avec z_buffer methode [sixth out image](https://github.com/RidaMohamed/Projet_RDV_Salhi_Abdelaziz/blob/master/out/out_num_6.png) ou nous avions rencontrer une petite erreur [sixth_fixed out image](https://github.com/RidaMohamed/Projet_RDV_Salhi_Abdelaziz/blob/master/out/out_sixth_fixed.png) au au debut. 

#### Troisieme etape
Dans cette etape nous avons fait l'affichage du monstre avec la matrice de projection
et le viewport [seventh out image](https://github.com/RidaMohamed/Projet_RDV_Salhi_Abdelaziz/blob/master/out/out_seventh.png).

#### 4eme etape
En derniere etape nous avons utiliser light pour l'affichge de monstre [ninth out image](https://github.com/RidaMohamed/Projet_RDV_Salhi_Abdelaziz/blob/f95a3b173cac55c41a211375c8b05465c9248313/out/out_ninth.ppm),apres au lieu de lumiere normal nous avons utliser une lumiere smooth 
[eleven out image](https://github.com/RidaMohamed/Projet_RDV_Salhi_Abdelaziz/blob/master/out/out_eleven.png), et pour finir nous avons fait la 3d avec la creation de 2 images ensuite faire le decalge de ces 2 derniers 
pour avoir en fin une vision 3d [3d_image out image](https://github.com/RidaMohamed/Projet_RDV_Salhi_Abdelaziz/blob/5e39b7f35aa13f31309f5af1b725e766fbae66b8/out/out_3d_image.png).

## compilation (de derniere version)
``` sh 
git clone https://github.com/RidaMohamed/Projet_RDV_Salhi_Abdelaziz.git
cd Projet_RDV_Salhi_Abdelaziz
mkdir build
cd build
cmake ..
make
```
## Final image 3D
![3d image ](https://github.com/RidaMohamed/Projet_RDV_Salhi_Abdelaziz/blob/5e39b7f35aa13f31309f5af1b725e766fbae66b8/out/out_3d_image.png)

## License
Free to use
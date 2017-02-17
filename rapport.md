Question 1
-----------
Notes: le code de ce numéro est dans le fichier "q1.c"

4. Sachant que les discontinuités verticales dans le domaine spatial se transforme en densité de fréquences horizontales 
   dans le domaine fréquentiel, et vice versa(discontinuités horizontales devenant densité verticale), 
   il est logique d'associer le spectre de D1r à D1r, puisque ce spectre est visiblement dense sur l'axe verticale, et contient
   aussi une bande moins dense mais tout de même visible de fréquences à l'horizontale, correspondant
   à la discontinuité horizontale plus marquée associée aux tuiles rectangulaire(plus larges que hautes).
   De même, le spectre de D11r contient trois bandes de fréquences discontinues à l'horizontale, qu'on peut très bien
   associer aux bandes verticales de l'image D11r. De plus, Les rayures diagonales dans les bandes verticales de D11r
   sont aussi visible dans l'augmentation de la densité de fréquence vers les extrémités des bandes du spectre, formant
   une densité diagonale. Enfin, le spectre de D46r est facilement discernable par ses bandes de fréquence diagonales,
   qu'on peut associer au quadrillage diagonale de l'image spatiale.

Question 2
-----------

Notes: le code de ce numéro est dans le fichier "q2.c"

a. On supprime des bandes diagonales formant un "X" dans le spectre. Ceci provoque des perturbations diagonales dans l'image spatiale.  

b. Il s'agit d'un filtre passe-bas: on supprimes les fréquences supérieur à la valeur correspondant à cette distance du centre
    (les hautes fréquences sont plus éloignées du centre). On perd ainsi les détails de l'image, générant une image spatiale flou.
c. Les hautes fréquences(distance euclidienne par rapport au centre plus élevée) sont amplifiée par rapport aux basses fréquences. 
    Les détails ressortent.

d. On fait un filtre passe-bas(en supprimant les hautes fréquences) sur l'axe verticale de l'image spatiale
    (les axes étant inversées par rapport au spectre). Ceci provoque des distortion sur la verticale, correspondant à la
    perte d'information de détail sur cette axe.
    
e. Même chose, mais sur l'autre axe(perte d'information de détail sur l'axe horizontale).

Question 3
-----------
Notes: le code de ce numéro est dans le fichier "q3.c"

1. Lorsqu'on limite l'information reçu, les détails de l'image(les hautes fréquences) 
   sont perdus avant les composantes "brutes" ou génériques(correspondant aux basses fréquences).
   Cette image est composée des basses fréquences d'une image de Marilyn Monroe et des hautes
   fréquences d'une image de Einstein. On peut construire une telle image simplement
   en coupant(mettant à zéro) les basses fréquences de l'image de Einstein, de même avec
   les hautes fréquences de l'image de Monroe, et en superposant(additionant) les résultats.
   
2. a. l'image vu de loin(celle qui est cachée par les détails lorsque vu de près) 
   est la partie "Monroe" de l'image composite. L'opération permettant de percevoir 
   cette information de près serait d'amplifier les basses fréquences et/ou 
   d'atténuer les hautes fréquences.
   
2.b Incomplété


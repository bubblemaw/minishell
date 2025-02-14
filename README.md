PLAN DE MINSHELL

(1) boucle infini qui attend un str ce str etant la commande souhaitee
    - afficher un prompt qui attend une commande
    - Tokkenisation de la commande

        - Les commandes doivent obligatoirement etre separees par un ou plusieurs
            espaces
        - les options egalement
        - mais les redirection peuve etre collees ou avoir plusieurs espaces
        - quand on crée des variables tout doit être collé avant et apres le =
        - si on detecte des "" ou '' c est considere comme
 		  un separateur jusqu a ce qu on le retrouve

        - GESTIONS A DISTINGUER EN TYPE
            - tab en 2 dimensions
            - commande + arguments / options
            - a voir pour les redirections
            - ajout pour les append

        - mettre un flag begin et end pour savoir de ou a ou va le mot dans le string
        - injecter cette partie du string dans un noeud de la liste chainee
        - pour injecter le noeud il faut faire un substr de la partie du string
	        que l on souhaite prendre

        GESTION ERREUR DES TOKKENS
        - verifier l'ordre des elements
        - verifier la validiter de la commande
        - verifier la validiter des redirection

(2) parsing pour aller chercher les commandes
    - verifier tous les chemins du PATH, donc mettre **env en arg
    - verifier si la commande est executable (execve)
    - gerer une erreur si la commande n'est pas trouvee

//-------------------------------------------------------------------------------//

(3) execution des commandes.
    (2)
    - comparaisons de verifications de commande
        - comparer les tokken recus avec les foncions du PATH ou les built in
    (4)
    - creation du processsus enfant
    - gere les redirection avec les fonctions
    - execution de l'enfant
    - mise en attente du parent (waitpid)

(4) redirection des inputs/outputs et pipe
    - une fonction pour chaque type de redirection
        - inputs / outputs
            - > redirige dans un fichier et ecrase
            - >> redirige mais n ecrase pas
            - < redirige un fichier vers une commande
            - << pas bien compris pour le moment
        - pipe
            - la sortie avant | devient l entree de la prochaine commande
    - appliquer n'importe quelle fonction de redirection a un tokken
        - quotes ''  $ a gerer
            - '' = Afficher tous les char sans aucune interpretation
            -  = les char doivent etre interprete dchellen
            - sans quotes, interpretation

recodage des commandes internes built in
    - echo with -n (le n enleve le retour a la ligne automatique)
    - cd     (deplacements)
    - pwd    (affiche le repertoire courrant)
    - export (modifie le nom d'une variable env ou cree si existe pas)
    - unset  (desactive une variable d environnement)
    - env    (affiche l environnement)
    - exit   (quitte le terminal)
        - la commande exit doit return la bonne valeur de sortie si on fait echo
gestion des signaux ctrl-C ctrl-D ctr-    - sigint
    - sigquit

historique
    - gerer un historique qui repertorie TOUTES les commandes effectuers


//-------------------------------------------------------------------------------//

QUELQUES TEST DE fonctions

echo

dchellen@c1r7s1:~/Desktop/minishell$ echo "bonjour"
bonjour
dchellen@c1r7s1:~/Desktop/minishell$ echo "bonjour" "ca va"
bonjour ca va
dchellen@c1r7s1:~/Desktop/minishell$ echo "bonjour""ca va"
bonjourca va
dchellen@c1r7s1:~/Desktop/minishell$ echo ""bonjour" "ca va""
bonjour ca va
dchellen@c1r7s1:~/Desktop/minishell$ echo "bonjour" "ca va"
bonjour ca va
dchellen@c1r7s1:~/Desktop/minishell$ echo "bonjour" "ca va" 'eh'
bonjour ca va eh
dchellen@c1r7s1:~/Desktop/minishell$ echo "bonjour" "ca va" 'eh''
> ^C
dchellen@c1r7s1:~/Desktop/minishell$ echo "bonjour"""
bonjour
dchellen@c1r7s1:~/Desktop/minishell$ echo "bonjour"""""
bonjour
dchellen@c1r7s1:~/Desktop/minishell$ echo "bonjour"""""""
bonjour
dchellen@c1r7s1:~/Desktop/minishell$ echo "bonjour""""""""
> ^C
dchellen@c1r7s1:~/Desktop/minishell$ echo "bonjour" "ca va"
bonjour ca va
dchellen@c1r7s1:~/Desktop/minishell$ echo "bonjour" " ca va"
bonjour  ca va
dchellen@c1r7s1:~/Desktop/minishell$ echo "bonjour" "ca va"
bonjour ca va

//-----------------------------------------------------------------------------//

GESTION DES PRIORITEES EN BASH

1. preparer l entree avec les redirection
    < et << prennent ce qu il y a a droite 
    et en font l'entree de l'element a gauche

2. transmissions entre processsusavec les pipes
    transmissions des entree et sortie a tranvers Les
    child processsus

3. executer la commande
    execture la commande avec les redirections au 
    prealable

4. rediriger vers la sortie
    prendre la sortie de l'exec de la commande et
    le mettre dans la sortie

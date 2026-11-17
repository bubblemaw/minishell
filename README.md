# Minishell

Minishell est un shell minimaliste écrit en C, inspiré du comportement de
`bash`. Le projet implémente la lecture, l'analyse et l'exécution de commandes
dans un terminal interactif.

## Fonctionnalités

- prompt interactif avec historique via Readline ;
- exécution de commandes externes trouvées dans `PATH` ;
- arguments et options ;
- pipes (`|`) ;
- redirections :
  - entrée (`<`) ;
  - sortie avec écrasement (`>`) ;
  - sortie en mode append (`>>`) ;
  - heredoc (`<<`) ;
- guillemets simples et doubles ;
- expansion des variables d'environnement ;
- builtins :
  `echo`, `cd`, `pwd`, `export`, `unset`, `env` et `exit` ;
- gestion des signaux du terminal.

## Plateforme cible et prérequis

Le projet est principalement conçu pour **Linux**, qui constitue la plateforme
cible. La gestion des signaux utilise `rl_replace_line()`, disponible dans
l'environnement Readline attendu sous Linux.

macOS n'est pas la plateforme cible et peut nécessiter des adaptations liées à
la version de Readline fournie par le système. La compilation et le support
complet ne sont donc pas garantis sur macOS.

- Linux (plateforme recommandée) ;
- compilateur C compatible avec `cc` ;
- `make` ;
- bibliothèque Readline (`libreadline`).

Sur Debian/Ubuntu, les dépendances peuvent être installées avec :

```bash
sudo apt install build-essential libreadline-dev
```

Sur macOS, Readline peut être installée avec Homebrew, mais cette plateforme
n'est pas la cible principale :

```bash
brew install readline
```

## Compilation

```bash
make
```

Pour supprimer les fichiers générés :

```bash
make clean
make fclean
```

Pour recompiler entièrement :

```bash
make re
```

## Utilisation

```bash
./minishell
```

Exemples :

```bash
echo "hello world"
pwd
ls -la | grep minishell
echo "$HOME"
cat < input.txt > output.txt
cat << EOF
contenu du heredoc
EOF
```

## Organisation du projet

- `srcs/main/` : point d'entrée et initialisation ;
- `srcs/tokken/` : tokenisation et validation des tokens ;
- `srcs/token_to_cmd/` : conversion des tokens en commandes ;
- `srcs/cmd_parsing/` : recherche des exécutables ;
- `srcs/execution/` : exécution et gestion des pipes ;
- `srcs/redirection/` : redirections et heredocs ;
- `srcs/expansion/` : variables, guillemets et expansions ;
- `srcs/builtin/` : commandes internes ;
- `srcs/error_free/` : erreurs et libération mémoire ;
- `srcs/utils/` : fonctions utilitaires et signaux ;
- `libft/` : bibliothèque C personnalisée ;
- `GNL/` : fonctions de lecture de lignes ;
- `inc/minishell.h` : structures et prototypes principaux.

## État du projet

La branche `develop` a été fusionnée dans `main`. Le projet compile avec
`make` et contient désormais l'implémentation complète prévue pour le shell.
Des tests complémentaires restent recommandés pour valider tous les cas
limites, notamment les erreurs de syntaxe, les heredocs et les signaux.

## Licence

Projet personnel / projet académique.

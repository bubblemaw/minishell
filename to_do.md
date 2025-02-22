# Erreur

# 1	
	minishell$ echo 'c'e'st'

	node[0] -> echo
	node[1] -> 'c'
	node[2] -> e'st'

	doit etre
	node[0] -> echo
	node[1] -> 'c'
	node[2] -> e
	node[3] -> 'st'
# 2
	la meme que la #1 avec les doubles quotes
# 3
	cas un peu tricky
	minishell$ echo $"hello, world"

	node[0] -> echo
	node[1] -> $"hello,
	node[2] -> world"

	devrait sortir
	minishell$ echo $"hello, world"

	node[0] -> echo
	node[1] -> $"hello, world"

	cette présentation avec le $avant le double guillemets 
	sert a chercher un traduction dans le shell local si le shell
	ne trouve pas "traduction" au mot il l'affiche de base 


# A FAIRE OU A TESTER

## TEST DE COMMANDES

**variables**

creations de variables
``` bash
david@david-Vivobook$ var==test
david@david-Vivobook$ echo $var
=test
david@david-Vivobook$ var=="test"
david@david-Vivobook$ echo $var
=test
```

## PARSING DES TOKENS

# 1
	important de mettre le type
	si single quotes pas d'expansion de variable echo '$USER' = $USER
	si double quotes expansion					echo "$USER" = Maw42 

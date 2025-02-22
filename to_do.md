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

# A FAIRE OU A TESTER

## TEST DE COMMANDES

**variables**

``` bash
david@david-Vivobook$ var==test
david@david-Vivobook$ echo $var
=test
david@david-Vivobook$ var=="test"
david@david-Vivobook$ echo $var
=test
```

## PARSING DES TOKENS

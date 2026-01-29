# Minishell — Structure et arborescence du projet

**Auteur :** Anthony  
**Date :** 06.01.2026  
**Version :** 1.0  

---

## Objectif du document
Ce document décrit :
- l’arborescence du projet minishell
- la séparation logique des responsabilités
- le rôle précis de chaque dossier du projet

L’objectif est de :
- faciliter le travail à plusieurs
- limiter les conflits Git
- rendre le code plus lisible et maintenable

---

## Arborescence générale

```text
minishell/
├─ Makefile
├─ README.md
├─ .gitignore
├─ include/
│  ├─ minishell.h
│  ├─ ast.h
│  ├─ lexer.h
│  ├─ parser.h
│  ├─ expand.h
│  ├─ exec.h
│  ├─ builtins.h
│  ├─ env.h
│  ├─ signals.h
│  ├─ errors.h
│  └─ utils.h
├─ libft/
│  ├─ Makefile
│  ├─ include/
│  └─ src/
├─ src/
│  ├─ main.c
│  ├─ shell/
│  ├─ lexer/
│  ├─ parser/
│  ├─ expand/
│  ├─ ast/
│  ├─ exec/
│  ├─ builtins/
│  ├─ env/
│  ├─ signals/
│  ├─ errors/
│  └─ utils/
├─ tests/
│  └─ ...
└─ .github/
   ├─ pull_request_template.md
   └─ workflows/
      └─ ci.yml    (optionnel)
````

---

## Dossier `/include`

📌 **Contient les headers du projet**

* Déclare toutes les structures (`struct`)
* Déclare les prototypes de fonctions
* Sert de **contrat** entre les différents modules

⚠️ Toute modification ici doit être faite avec précaution (et idéalement review).

---

## Dossier `/src/main.c`

🎯 **Point d’entrée du programme**

Responsabilités :

* initialisation du shell
* appel de la boucle principale (REPL)
* nettoyage avant sortie

Ne contient **aucune logique métier complexe**.

---

## Dossier `/src/shell`

🧠 **Logique haut niveau du shell**

### Rôle

Orchestrer le fonctionnement global du shell sans implémenter les détails.

### Gère :

* affichage du prompt
* boucle principale (Read → Parse → Execute)
* initialisation globale
* nettoyage global

### Exemples de fichiers :

* `prompt.c`
* `repl.c`
* `init.c`
* `cleanup.c`

---

## Dossier `/src/lexer`

✂️ **Analyse lexicale (tokenisation)**

### Rôle

Transformer une ligne de texte brute en une liste de tokens.

### Gère :

* espaces et séparateurs
* opérateurs : `|`, `<`, `>`, `>>`, `<<`
* guillemets simples `'` et doubles `"`
* création de structures `t_token`

### Exemple de structure :

```c
t_token {
    type;
    value;
    next;
}
```

### Sortie typique :

* liste chaînée ou tableau de tokens

### Exemples de fichiers :

* `lexer.c`
* `lexer_tokens.c`
* `lexer_quotes.c`
* `lexer_utils.c`

---

## Dossier `/src/parser`

🏗️ **Analyse syntaxique**

### Rôle

Donner du sens à la liste de tokens et construire une structure exécutable.

### Gère :

* pipelines : `cmd | cmd | cmd`
* association des redirections à la bonne commande
* construction de `argv`
* validation syntaxique basique :

  * `|` au début ou à la fin
  * redirection sans fichier
  * quotes non fermées

### Sortie typique :

* liste de commandes (`t_cmd`)
* ou structure AST/pipeline

### Exemples de fichiers :

* `parser.c`
* `parser_pipeline.c`
* `parser_redirs.c`
* `syntax.c`

---

## Dossier `/src/expand`

🔄 **Expansion des éléments shell**

### Rôle

Appliquer les règles d’expansion Bash-like.

### Gère :

* expansion des variables `$VAR`
* expansion de `$?`
* suppression des quotes
* règles `'` vs `"` (pas d’expansion dans `'`)

⚠️ Ne lance aucune commande.

### Exemples de fichiers :

* `expand.c`
* `expand_vars.c`
* `expand_quotes.c`

---

## Dossier `/src/ast`

🌳 **Représentation interne exécutable**

### Rôle

Stocker la structure finale prête à être exécutée.

### Gère :

* création des structures finales (`t_cmd`, `t_redir`, `t_pipeline`)
* libération mémoire complète
* outils de debug (optionnel)

### Exemples de fichiers :

* `ast_build.c`
* `ast_free.c`
* `ast_debug.c`

---

## Dossier `/src/exec`

🚀 **Exécution des commandes**

### Rôle

Exécuter réellement les commandes via le système.

### Gère :

* `fork()`, `execve()`
* pipes (`|`)
* redirections (`<`, `>`, `>>`)
* heredoc (`<<`)
* `waitpid` et codes de retour (`$?`)

### Exemples de fichiers :

* `executor.c`
* `exec_pipeline.c`
* `exec_redirs.c`
* `heredoc.c`

---

## Dossier `/src/builtins`

🏠 **Commandes internes du shell**

### Rôle

Implémenter les commandes qui ne passent pas par `execve`.

### Commandes :

* `echo`
* `cd`
* `pwd`
* `export`
* `unset`
* `env`
* `exit`

⚠️ Certaines doivent s’exécuter dans le **processus parent** (`cd`, `export`, `unset`, `exit`).

### Exemples de fichiers :

* `builtin_cd.c`
* `builtin_export.c`
* `builtins_dispatch.c`

---

## Dossier `/src/env`

🌱 **Gestion de l’environnement**

### Rôle

Gérer les variables d’environnement du shell.

### Gère :

* stockage interne (liste / tableau)
* `get`, `set`, `unset`
* conversion vers `char **envp` pour `execve`

### Exemples de fichiers :

* `env_init.c`
* `env_get.c`
* `env_set.c`

---

## Dossier `/src/signals`

⚡ **Gestion des signaux**

### Rôle

Gérer le comportement du shell face aux signaux.

### Gère :

* `Ctrl-C` au prompt
* `Ctrl-C` en exécution
* `Ctrl-C` dans heredoc
* `Ctrl-\`

### Exemples de fichiers :

* `signals_prompt.c`
* `signals_child.c`
* `signals_heredoc.c`

---

## Dossier `/src/errors`

❌ **Gestion centralisée des erreurs**

### Rôle

Uniformiser les messages d’erreur et les codes de retour.

### Gère :

* messages utilisateur
* mapping erreurs → codes (`126`, `127`, etc.)
* wrappers autour de `perror`

---

## Dossier `/src/utils`

🧰 **Fonctions utilitaires**

### Rôle

Contenir uniquement des helpers génériques.

### Exemples :

* fonctions sur les chaînes
* gestion de tableaux (`char **`)
* helpers mémoire
* debug

⚠️ Aucune logique métier ici.

---

## Résumé

Chaque dossier correspond à **une étape logique du shell** :

* `lexer` → découper
* `parser` → structurer
* `expand` → transformer
* `exec` → exécuter
* `builtins` → commandes internes
* `signals` → interaction utilisateur

Cette séparation permet :

* un code plus clair
* un travail à plusieurs efficace
* une maintenance plus simple


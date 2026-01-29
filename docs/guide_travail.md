# Workflow Git — Collaboration à plusieurs (42)

## Objectif
Travailler à plusieurs sans se marcher dessus :
- `main` reste toujours stable (compilable / testable)
- chacun travaille sur sa branche
- on intègre via Pull Request (PR) + review rapide
- on évite de commit des fichiers générés

---

## 0) Pré-requis (à faire une fois)
### Vérifier l’identité Git
```bash
git config --global user.name "Prénom Nom"
git config --global user.email "mail@42.fr"
````

### Cloner le repo (une seule personne le crée, tout le monde le clone)

```bash
git clone <URL_DU_REPO>
cd <repo>
```

### Ajouter un .gitignore (important)

Exemples classiques pour du C à 42 :

* `*.o`, `*.a`, `*.out`
* `minishell` (binaire)
* dossiers de build / debug
* `.DS_Store` (mac), etc.

---

## 1) Règles simples (à respecter)

1. **Ne jamais coder directement sur `main`.**
2. **Une feature / un fix = une branche dédiée.**
3. **Commits petits et clairs** (pas “wip” toute la journée).
4. **Pull avant de push** (pour éviter les surprises).
5. **PR obligatoire** (même à deux) + mini review.

---

## 2) Branches : convention

* `main` : stable
* `feat/<sujet>` : nouvelle fonctionnalité
* `fix/<sujet>` : correction
* `refacto/<sujet>` : refactor
* `doc/<sujet>` : production/correction documentation

  Exemples :
* `feat/parser`
* `fix/leaks-export`
* `refacto/executor`

---

## 3) Démarrer une tâche (routine quotidienne)

### 3.1 Mettre à jour sa copie locale

```bash
git checkout main
git pull
```

### 3.2 Créer une branche de travail

```bash
git checkout -b feat/nom-de-la-tache
```

---

## 4) Travailler + commit

### 4.1 Voir l’état

```bash
git status
git diff
```

### 4.2 Ajouter les fichiers pertinents

```bash
git add <fichier1> <fichier2>
# ou
git add .
```

### 4.3 Commit (message clair)

```bash
git commit -m "parser: handle double quotes"
```

Bon format : `module: action courte`

* `lexer: ...`
* `exec: ...`
* `builtins: ...`
* `signals: ...`

---

## 5) Push sur le repo distant

La première fois sur une branche :

```bash
git push -u origin feat/nom-de-la-tache
```

Ensuite :

```bash
git push
```

---

## 6) Ouvrir une Pull Request (PR)

Sur GitHub/GitLab/Intra (selon votre repo), créer une PR :

* **source** : votre branche (`feat/...`)
* **target** : `main`

Checklist PR :

* [ ] compile
* [ ] pas de warnings
* [ ] tests manuels rapides OK
* [ ] pas de fichiers générés (binaires / .o)
* [ ] commit(s) lisibles

---

## 7) Mettre à jour sa branche si `main` a avancé

Deux options : **merge** (simple) ou **rebase** (plus propre, mais à manipuler prudemment).

### Option A — Merge `main` dans ta branche (recommandé débutants)

```bash
git checkout main
git pull
git checkout feat/nom-de-la-tache
git merge main
```

Résoudre les conflits si besoin, puis :

```bash
git push
```

### Option B — Rebase (historique linéaire)

À utiliser si vous êtes à l’aise.

```bash
git checkout feat/nom-de-la-tache
git fetch origin
git rebase origin/main
```

Puis push (souvent avec force) :

```bash
git push --force-with-lease
```

---

## 8) Résoudre un conflit (procédure)

Quand Git dit conflict :

1. `git status` pour voir les fichiers en conflit
2. ouvrir les fichiers, chercher :

   * `<<<<<<<`
   * `=======`
   * `>>>>>>>`
3. choisir la bonne version (ou combiner)
4. marquer comme résolu :

```bash
git add <fichier_resolu>
git commit -m "merge: resolve conflicts"
```

5. pousser :

```bash
git push
```

---

## 9) Bonnes pratiques spécifiques “travail à deux”

### Répartition simple (évite les conflits)

//todo

### “Contrat” sur les fichiers partagés

* Un seul responsable à la fois sur un fichier très central (ex: `parser.c`) -> sinon, on se marche dessus.

### Revues rapides

Avant merge :

* l’autre lit la PR 2 minutes
* check : logique + style + pas d’oubli évident

---

## 10) Commandes utiles (antisèche)

```bash
git log --oneline --graph --decorate --all
git branch
git branch -vv
git remote -v
git fetch
git stash           # mettre de côté temporairement
git stash pop
```

---

## 11) “Plan de secours” si tu as cassé ta branche

### Revenir au dernier commit propre (perd les modifs non commit)

```bash
git reset --hard HEAD
```

### Annuler un commit (sans perdre les changements)

```bash
git reset --soft HEAD~1
```

### Récupérer un commit “perdu”

```bash
git reflog
# puis
git checkout <hash>
```

---

## 12) Rituel recommandé (simple)

* **Début de session** : `git checkout main && git pull`
* **Avant push** : `git status` + compile/test
* **Avant merge** : `git merge main` (ou rebase) + retest
* **Après merge** : supprimer branche si terminée (optionnel)

```bash
git branch -d feat/nom-de-la-tache
git push origin --delete feat/nom-de-la-tache
```

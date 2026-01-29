# Minishell — Organisation du travail & Todo list

## Objectif
Ce document décrit :
- la répartition du travail entre les membres du groupe
- les responsabilités de chacun
- une todo list claire par personne
- les règles de collaboration Git

But : avancer efficacement sans conflits et garder un `main` stable.

---

## Règles générales
- ❌ Aucun développement direct sur `main`
- ✅ Une branche par tâche (`feat/...`, `fix/...`)
- ✅ Merge uniquement via Pull Request / Merge Request (ou merge local contrôlé sur infra 42)
- ✅ Revue par l’autre membre avant intégration
- ✅ Petites PR/MR fréquentes

---

## Architecture globale (rappel)
Flux du shell :

[comment]: TODO

---

## Répartition des rôles

### 🅰️ Personne A — Parsing & Expansion
Responsable de transformer la ligne utilisateur en une structure exploitable.

Zones principales :
- `src/lexer/`
- `src/parser/`
- `src/expand/`
- `src/ast/` (création / free)

Ne fait PAS :
- fork
- execve
- gestion des pipes / redirections bas niveau

---

### 🅱️ Personne B — Execution & Builtins
Responsable de l’exécution réelle des commandes.

Zones principales :
- `src/exec/`
- `src/builtins/`
- `src/signals/`
- partie exécution de `src/env/`

Ne fait PAS :
- parsing syntaxique
- gestion des quotes / tokens

---

## Contrat d’interface (IMPORTANT)
Les deux membres s’accordent sur les structures définies dans `include/minishell.h`.

Après parsing + expansion :
- `argv` est prêt à être exécuté
- les quotes sont supprimées
- les variables sont expansées
- les redirections sont identifiées

L’executor **ne corrige rien**, il exécute.

---

## TODO LIST — Personne A (Lexer / Parser / Expand)

### Phase 0 — Setup
- [ ] Définir les structures (`t_token`, `t_cmd`, `t_redir`, `t_pipeline`)
- [ ] Ajouter headers correspondants
- [ ] Helpers de création / destruction AST

---

### Phase 1 — Lexer
- [ ] Découper une ligne en tokens
- [ ] Gérer espaces et séparateurs
- [ ] Reconnaître `| < > >> <<`
- [ ] Gérer quotes simples `'`
- [ ] Gérer quotes doubles `"`

---

### Phase 2 — Parser
- [ ] Construire une pipeline de commandes
- [ ] Associer redirections à chaque commande
- [ ] Détecter erreurs syntaxiques simples
  - pipe en début/fin
  - redirection sans cible

---

### Phase 3 — Expansion
- [ ] Expansion `$VAR`
- [ ] Expansion `$?`
- [ ] Respect règles `'` vs `"`
- [ ] Suppression finale des quotes
- [ ] Gestion des cas vides après expansion

---

### Phase 4 — AST & Cleanup
- [ ] Construction AST final
- [ ] Fonctions de `free` complètes
- [ ] (Optionnel) fonction de debug AST

---

## TODO LIST — Personne B (Exec / Builtins / Signals)

### Phase 0 — Setup
- [ ] Initialisation environnement (copie de envp)
- [ ] Gestion globale du status `$?`
- [ ] Helpers fd / close

---

### Phase 1 — Execution basique
- [ ] `fork()` / `execve()`
- [ ] Résolution PATH
- [ ] Gestion erreurs (127 / 126)
- [ ] Attente correcte des enfants (`waitpid`)

---

### Phase 2 — Pipes
- [ ] Création des pipes
- [ ] Duplication stdin/stdout
- [ ] Fermeture correcte des fd
- [ ] Exécution pipelines multiples

---

### Phase 3 — Redirections
- [ ] `<` input
- [ ] `>` output
- [ ] `>>` append
- [ ] Intégration avec pipes

---

### Phase 4 — Builtins
- [ ] `echo`
- [ ] `pwd`
- [ ] `env`
- [ ] `cd`
- [ ] `export`
- [ ] `unset`
- [ ] `exit`

Règle :
- builtins **hors pipeline** → parent
- builtins **dans pipeline** → child

---

### Phase 5 — Heredoc & Signaux
- [ ] Parsing heredoc (depuis AST)
- [ ] Lecture heredoc
- [ ] Ctrl-C stop heredoc
- [ ] Signaux :
  - prompt
  - child
  - heredoc

---

## Organisation Git (rappel)

### Branches
- `main` : stable
- `feat/lexer`
- `feat/parser`
- `feat/expand`
- `feat/exec`
- `feat/builtins`

---

### Cycle de travail
1. Créer branche
2. Coder
3. Commit clair
4. Push
5. PR/MR
6. Review
7. Merge
8. Sync `main`

---

## Règle finale
> **Un code non relu est un bug en puissance.**

Même à deux :
- une review courte
- un `main` propre
- moins de stress à l’exam

---

## Statut du projet
- Parsing : ⬜ / 🟨 / 🟩
- Expansion : ⬜ / 🟨 / 🟩
- Execution : ⬜ / 🟨 / 🟩
- Builtins : ⬜ / 🟨 / 🟩
- Signaux : ⬜ / 🟨 / 🟩

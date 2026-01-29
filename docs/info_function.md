# Minishell — Fonctions autorisées et leur rôle

Ce document regroupe les principales fonctions autorisées pour le projet **minishell**, avec :
- leur prototype
- leur rôle
- leur usage typique dans minishell

---

## 📥 Lecture de l’entrée utilisateur (Readline)

### `readline`
```c
char *readline(const char *prompt);
````

📖 [https://man7.org/linux/man-pages/man3/readline.3.html](https://man7.org/linux/man-pages/man3/readline.3.html)

* Lit une ligne depuis le terminal.
* Affiche `prompt` comme invite (si `NULL`, aucune invite).
* La chaîne retournée est **allouée avec `malloc`** → **doit être `free`**.
* Retourne `NULL` en cas d’EOF (`Ctrl-D`).

👉 Utilisé pour lire la commande utilisateur dans la boucle principale.

---

### `add_history`

```c
void add_history(const char *line);
```

* Ajoute une ligne à l’historique du shell.
* Permet la navigation avec ↑ / ↓.

👉 À appeler uniquement si la ligne n’est pas vide.

---

### `rl_clear_history`

```c
void rl_clear_history(void);
```

* Supprime entièrement l’historique de readline.
* Libère aussi les structures internes de readline.

👉 À appeler à la fermeture du shell.

---

### Fonctions readline avancées (gestion Ctrl-C)

```c
void rl_replace_line(const char *text, int clear_undo);
int  rl_on_new_line(void);
void rl_redisplay(void);
```

* `rl_replace_line` : remplace la ligne courante
* `rl_on_new_line` : indique que l’on passe à une nouvelle ligne
* `rl_redisplay` : force le rafraîchissement de l’affichage

👉 Utilisées pour gérer proprement `Ctrl-C` au prompt.

---

## 🧬 Gestion des processus

### `fork`

```c
pid_t fork(void);
```

* Crée un **processus enfant**.
* Retour :

  * `0` dans l’enfant
  * PID de l’enfant dans le parent
  * `-1` en cas d’erreur

👉 Utilisé pour exécuter une commande externe.

---

### `execve`

```c
int execve(const char *pathname, char *const argv[], char *const envp[]);
```

* Remplace le processus courant par un programme.
* Ne retourne **que si erreur**.

👉 Utilisé dans le **processus enfant** après `fork`.

---

### `wait`, `waitpid`

```c
pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);
```

* Attend la fin d’un ou plusieurs processus enfants.
* Permet de récupérer le **code de retour** (`$?`).

👉 Indispensable pour la synchronisation des commandes.

---

## 🔀 Pipes et redirections

### `pipe`

```c
int pipe(int pipefd[2]);
```

* Crée un canal de communication :

  * `pipefd[0]` → lecture
  * `pipefd[1]` → écriture

👉 Utilisé pour implémenter `|`.

---

### `dup`, `dup2`

```c
int dup(int oldfd);
int dup2(int oldfd, int newfd);
```

* Duplique un descripteur de fichier.
* `dup2` permet de rediriger vers un FD précis (`STDIN`, `STDOUT`).

👉 Utilisé pour `<`, `>`, `>>` et les pipes.

---

## 📂 Système de fichiers

### `stat`, `lstat`, `fstat`

```c
int stat(const char *path, struct stat *buf);
int lstat(const char *path, struct stat *buf);
int fstat(int fd, struct stat *buf);
```

* Récupèrent des informations sur un fichier.
* `lstat` ne suit pas les liens symboliques.

👉 Vérification d’existence, permissions, type de fichier.

---

### `access`

```c
int access(const char *pathname, int mode);
```

* Vérifie l’accès à un fichier.
* Modes :

  * `F_OK` : existe
  * `R_OK` : lisible
  * `W_OK` : modifiable
  * `X_OK` : exécutable

👉 Utilisé pour résoudre les commandes (`PATH`).

---

### `unlink`

```c
int unlink(const char *pathname);
```

* Supprime un fichier.

👉 Rarement utilisé dans minishell, mais autorisé.

---

## 📁 Répertoires

### `opendir`, `readdir`, `closedir`

```c
DIR *opendir(const char *name);
struct dirent *readdir(DIR *dirp);
int closedir(DIR *dirp);
```

* Permettent de parcourir un répertoire.

👉 Utilisés éventuellement pour `env`, `ls` custom (bonus).

---

## 📍 Répertoire courant

### `getcwd`

```c
char *getcwd(char *buf, size_t size);
```

* Retourne le chemin du répertoire courant.

👉 Utilisé pour `pwd`.

---

### `chdir`

```c
int chdir(const char *path);
```

* Change le répertoire courant.

👉 Utilisé pour `cd` (dans le parent !).

---

## 🌱 Environnement

### `getenv`

```c
char *getenv(const char *name);
```

* Récupère la valeur d’une variable d’environnement.

👉 Utilisé pour `$VAR`, `PATH`, `HOME`, etc.

---

## ⌨️ Terminal & signaux

### `isatty`

```c
int isatty(int fd);
```

* Vérifie si un FD est relié à un terminal.

---

### `ttyname`

```c
char *ttyname(int fd);
```

* Retourne le nom du terminal associé.

---

### `ioctl`

```c
int ioctl(int fd, unsigned long request, ...);
```

* Commandes bas niveau sur le terminal.

👉 Rare, mais parfois utile pour la gestion avancée.

---

### `tcgetattr`, `tcsetattr`

```c
int tcgetattr(int fd, struct termios *termios_p);
int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);
```

* Permettent de modifier le comportement du terminal.

👉 Utiles pour gérer Ctrl-C, echo, heredoc.

---

## 📜 Termcap (gestion affichage)

```c
int  tgetent(char *bp, const char *name);
int  tgetflag(const char *id);
int  tgetnum(const char *id);
char *tgetstr(const char *id, char **area);
char *tgoto(const char *cap, int col, int row);
int  tputs(const char *str, int affcnt, int (*putc)(int));
```

👉 Utilisés pour le contrôle bas niveau de l’affichage terminal
(peu utilisés dans minishell classique).

---

## 📤 Règles pour `export`

* ❌ pas d’espace
* ❌ ne pas commencer par un chiffre
* ✅ caractères autorisés :

  * `a-z`
  * `A-Z`
  * `0-9`
  * `_`

Exemples valides :

```bash
export A=42
export MY_VAR=test
```

Invalides :

```bash
export 1ABC=42
export A-B=42
```

---

## 🧠 À retenir

* `readline` → entrée utilisateur
* `fork + execve` → exécution
* `dup2 + pipe` → redirections / pipes
* `waitpid` → synchronisation
* `cd / export / exit` → **parent obligatoire**

# Vim2

This started as a project for UConn's CSE 3150 course with Professor Yufeng Wu. The task was to design and implement a text editor that replicated Vim's functionality somewhat simplistically. Now, I just add stuff to it periodically because it's fun. Unfortunately, it will never outpace the real thing, or VSCode, or really any other text editor. Fun project, though!

## Tutorial

### Building the Editor

1. Navigate to the `TextViewImpCode/` directory:
   ```bash
   cd TextViewImpCode/
   ```

2. Build the editor:
   ```bash
   make
   ```

3. The executable `myeditor` will be created in the same directory.

### Running the Editor

#### Demo Mode (No File)
Run without arguments to start the editor with an empty document:
```bash
./myeditor
```
This will show "Press ctrl-q to quit" and you can start typing immediately. Press `Ctrl+Q` to quit.

#### Editing a File
Open an existing file or create a new one:
```bash
./myeditor filename.txt
```

### Using the Editor

The editor has two modes, similar to Vim:

#### Command Mode (Default)
- **Navigation**: Use arrow keys to move the cursor
- **Switch to Edit Mode**: Press `i` to enter insert mode
- **Quit**: Press `q` to quit immediately, or `Ctrl+Q` to quit and save

#### Edit Mode
- **Insert Text**: Type normally to insert characters at cursor position
- **New Line**: Press `Enter` to create a new line
- **Backspace**: Press `Backspace` to delete characters
- **Exit Edit Mode**: Press `Escape` to return to command mode

#### Undo/Redo
- **Undo**: `Ctrl+Z` (works in both modes)
- **Redo**: `Ctrl+Y` (works in both modes)

### Key Controls

| Key | Action |
|-----|--------|
| `Arrow Keys` | Navigate cursor |
| `i` | Enter edit/insert mode |
| `Escape` | Enter command mode |
| `q` | Quit immediately (command mode) |
| `Enter` | New line (edit mode) |
| `Backspace` | Delete character |
| `Ctrl+Q` | Quit and save |
| `Ctrl+Z` | Undo |
| `Ctrl+Y` | Redo |

### Example Session

1. Start the editor:
   ```bash
   ./myeditor myfile.txt
   ```

2. Press `i` to enter edit mode

3. Type some text:
   ```
   Hello, World!
   This is my text editor.
   ```

4. Press `Escape` to return to command mode

5. Use arrow keys to navigate

6. Press `Ctrl+Q` to save and quit

The file will be automatically saved when you quit the editor.

# To-Do List for Input Parsing

## General Setup
1. Open and read the `.rt` file line by line.
2. Split each line into tokens based on spaces and commas.
3. Identify the type of element (e.g., `A`, `C`, `L`, `sp`, etc.).
4. Validate the format and values of each line based on the element type.

---

## Validation for Single-Instance Elements
1. **Ambient Lighting (`A`)**:
   - Ensure only one `A` element exists in the file.
   - Validate:
     - Ratio is a float in the range `[0.0, 1.0]`.
     - RGB values are integers in the range `[0, 255]`.
   - Provide an error if a duplicate `A` is found.

   **Example**:
   ```plaintext
   Valid: A 0.2 255,255,255
   Invalid: A 1.5 255,255,255 // Ratio exceeds 1.0
   Duplicate: A 0.2 255,255,255
             A 0.5 100,100,100
   ```

2. **Camera (`C`)**:
   - Ensure only one `C` element exists in the file.
   - Validate:
     - Position contains three valid float values.
     - Orientation vector contains three normalized float values (`-1.0 to 1.0`).
     - FOV is an integer in the range `[0, 180]`.
   - Provide an error if a duplicate `C` is found.

   **Example**:
   ```plaintext
   Valid: C -50,0,20 0,0,1 70
   Invalid: C -50,0,20 0,0,2 70 // Orientation vector is not normalized
   Duplicate: C -50,0,20 0,0,1 70
             C 0,0,0 0,1,0 60
   ```

---

## Validation for Multi-Instance Elements
1. **Light (`L`)**:
   - Allow multiple `L` elements.
   - Validate:
     - Position contains three valid float values.
     - Brightness ratio is a float in the range `[0.0, 1.0]`.
     - RGB values are integers in the range `[0, 255]`.

   **Example**:
   ```plaintext
   Valid: L -40,50,0 0.6 255,255,255
   Invalid: L -40,50,0 1.5 255,255,255 // Brightness ratio exceeds 1.0
   ```

2. **Sphere (`sp`)**:
   - Allow multiple `sp` elements.
   - Validate:
     - Center position contains three valid float values.
     - Diameter is a positive float.
     - RGB values are integers in the range `[0, 255]`.

   **Example**:
   ```plaintext
   Valid: sp 0,0,20 12.6 255,0,0
   Invalid: sp 0,0,20 -5 255,0,0 // Negative diameter
   ```

3. **Plane (`pl`)**:
   - Allow multiple `pl` elements.
   - Validate:
     - A point on the plane contains three valid float values.
     - Normal vector contains three normalized float values (`-1.0 to 1.0`).
     - RGB values are integers in the range `[0, 255]`.

   **Example**:
   ```plaintext
   Valid: pl 0,0,-10 0,1,0 0,255,0
   Invalid: pl 0,0,-10 0,2,0 0,255,0 // Normal vector not normalized
   ```

4. **Cylinder (`cy`)**:
   - Allow multiple `cy` elements.
   - Validate:
     - Center position contains three valid float values.
     - Orientation vector contains three normalized float values (`-1.0 to 1.0`).
     - Diameter is a positive float.
     - Height is a positive float.
     - RGB values are integers in the range `[0, 255]`.

   **Example**:
   ```plaintext
   Valid: cy 50,0,20 0,1,0 14.2 42.0 0,0,255
   Invalid: cy 50,0,20 0,2,0 14.2 42.0 0,0,255 // Orientation vector not normalized
   ```

---

## Error Handling
1. **Duplicate Single-Instance Elements**:
   - Return an error if more than one `A` or `C` is found.

   **Example**:
   ```plaintext
   A 0.2 255,255,255
   A 0.5 100,100,100 // Duplicate error
   ```

2. **Missing Required Elements**:
   - Ensure at least one `A` and one `C` are present in the file.

   **Example**:
   ```plaintext
   L -40,50,0 0.6 255,255,255
   sp 0,0,20 20 255,0,0
   // Error: Missing ambient light and camera
   ```

3. **Invalid Identifiers**:
   - Return an error if an unrecognized identifier is encountered.

   **Example**:
   ```plaintext
   X 1.0 0,0,255 // Unknown identifier
   ```

4. **Invalid Format**:
   - Check for missing or extra parameters in each line.

   **Example**:
   ```plaintext
   A 0.2 255,255 // Missing one RGB value
   C -50,0,20 0,0,1 // Missing FOV
   ```

5. **Invalid Value Ranges**:
   - Ensure all numeric values fall within their respective valid ranges.

   **Example**:
   ```plaintext
   A 1.2 255,255,255 // Ratio exceeds 1.0
   L -40,50,0 -0.5 255,255,255 // Brightness ratio below 0.0
   ```

---

## Dynamic Storage for Multi-Instance Elements
1. Use a list or array to store multiple lights (`L`), spheres (`sp`), planes (`pl`), and cylinders (`cy`).
2. Dynamically allocate memory for each new element during parsing.
3. Ensure proper memory cleanup after parsing is complete.

---

## Testing Edge Cases
1. Test with a file that has:
   - No `A` or `C` elements.
   - Duplicate `A` or `C` elements.
   - Valid and invalid formats for `L`, `sp`, `pl`, and `cy` elements.

   **Example**:
   ```plaintext
   A 0.2 255,255,255
   C -50,0,20 0,0,1 70
   L -40,50,0 0.6 255,255,255
   A 0.5 100,100,100 // Duplicate error
   ```

2. Test files with:
   - Mixed valid and invalid lines.

   **Example**:
   ```plaintext
   A 0.2 255,255,255
   sp 0,0,20 -5 255,0,0 // Negative diameter
   pl 0,0,-10 0,1,0 0,255,0
   ```

3. Validate handling of extreme values.

   **Example**:
   ```plaintext
   A -0.1 255,255,255 // Ratio below 0.0
   L -40,50,0 1.5 255,255,255 // Brightness ratio exceeds 1.0
   ```


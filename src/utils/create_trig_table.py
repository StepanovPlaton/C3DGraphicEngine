import math
import json

def generate_cos_table(size=360, output_file="cos_table.h"):
    angles = [2 * math.pi * i / size for i in range(size)]
    cos_values = [math.cos(angle) for angle in angles]

    with open(output_file, 'w') as f:
        f.write("#ifndef COS_TABLE_H\n")
        f.write("#define COS_TABLE_H\n\n")
        
        f.write("#include <math.h>\n\n")
        
        f.write("#ifndef M_PI\n")
        f.write("#define M_PI 3.14159265358979323846f\n")
        f.write("#endif\n\n")
        
        f.write("#ifndef M_PI_2\n")
        f.write("#define M_PI_2 1.57079632679489661923f\n")
        f.write("#endif\n\n")
        
        f.write("#define COS_TABLE_SIZE {}\n\n".format(size))
        
        f.write("static float cos_table_angles[COS_TABLE_SIZE] = {\n")
        for i in range(0, size, 8):
            line_values = []
            for j in range(i, min(i+8, size)):
                line_values.append(f"{angles[j]:.10f}f")
            f.write("    " + ", ".join(line_values) + ",\n")
        f.write("};\n\n")
        
        f.write("static float cos_table_values[COS_TABLE_SIZE] = {\n")
        for i in range(0, size, 8):
            line_values = []
            for j in range(i, min(i+8, size)):
                line_values.append(f"{cos_values[j]:.10f}f")
            f.write("    " + ", ".join(line_values) + ",\n")
        f.write("};\n\n")
        
        f.write("#endif\n")
    
    print(f"Таблица косинусов размером {size} точек сохранена в {output_file}")
    
    return {
        'size': size,
        'angles': angles,
        'cos': cos_values
    }

if __name__ == "__main__":
    n = int(input("Размер таблицы:"))
    print("Генерация таблиц косинусов...")
    generate_cos_table(n, "cos_table.h")
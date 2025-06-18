import json
import uuid

def convert_format(input_path, output_path):
    """
    将旧格式的课程数据转换为新的数据库格式.
    """
    try:
        with open(input_path, 'r', encoding='utf-8') as f:
            old_courses = json.load(f)
    except FileNotFoundError:
        print(f"错误: 输入文件 {input_path} 未找到")
        return
    except json.JSONDecodeError:
        print(f"错误: 无法解析 {input_path} 中的JSON")
        return

    new_courses = []
    for old_course in old_courses:
        new_course = {
            "name": old_course.get("name", ""),
            "building": old_course.get("building", ""),
            "room": old_course.get("room", ""),
            "teacher": old_course.get("teacher", ""),
            "uuid": str(uuid.uuid4()),
            "note": old_course.get("note", ""),
            "courseTime": old_course.get("courseTime", [[] for _ in range(7)]),
            "tags": old_course.get("tags", []),
            "comments": []
        }
        new_courses.append(new_course)

    new_db_structure = {
        "users": [],
        "courses": new_courses
    }

    with open(output_path, 'w', encoding='utf-8') as f:
        json.dump(new_db_structure, f, ensure_ascii=False, indent=4)

    print(f"成功将 {input_path} 转换为 {output_path}")

if __name__ == "__main__":
    input_file = "PKUAllCourses.json"
    output_file = "DB_PKUAllCourses_Empty.json"
    convert_format(input_file, output_file) 
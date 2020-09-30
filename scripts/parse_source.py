import sys

print(3)

sys.argv = [sys.argv[0], "D:\Dev\BHive\BHive\src\BHive\Components\Component.h",  "D:\Dev\BHive\BHive\src\BHive\Components\Component.generated.h"]  

source = open(sys.argv[1], 'r')

current_type = ""
attributes = {}
types = {}

for line in source:
    words = line.split()
    #skip empty lines
    if len(words) < 1:
        continue
        
    print(words)

    #start type
    if words[0] in {"struct", "class"} and current_type == "" and len(words) > 1 and ";" not in line:
        if words[1] in ["H_API", "HA_EMPTY_BASE"] and len(words) > 2:
            current_type = words[2]
        else:
            current_type = words[1]
        types[current_type] = {"attributes": attributes, "fields" :[]}
        #reset attributes for following fields
        attributes = {}
        continue
        #end type
    if(line.strip() == "};") and current_type != "":
        current_type = ""
        continue
    #detect a field
    if current_type != "" and words[0] == "PROPERTY":
        find_field_name_ender = lambda line: next((i for i, ch in enumerate(line) if ch in {"{", "=", ";"}), None)
        ind = find_field_name_ender(line)
        #if name is not on same line as type
        while not ind:
            line = next(source)
            ind = find_field_name_ender(line)
        field = line[:ind].split()[-1]
        types[current_type]["fields"].append({"name" : field, "attributes" : attributes})
        #reset attributes for field
        attributes = {}
    #detect
    if words[0].startswith("CLASS("):
        attributes_list = line.partition('(')[-1].rpartition(')')[0].split(",")
        for index, val in enumerate(attributes_list) : attributes_list[index] = val.strip()
        for attribute in attributes_list:
            if(attribute.startswith("tag::")):
                attributes["tag"] = attribute
            elif attribute.startswith("CALLBACK"):
                attributes["callback"] = attributes.partition('(')[-1].rpartition(')')[0]
            else:
                attributes[attribute] = True

source.close()

gen = open(sys.argv[2], 'w+')
gen.writelines('#pragma once\n\n')


for type in types:
    if not types[type]["fields"]:
        continue

    inline = ('inline') if "INLINE" in types[type]["attributes"] else ''

    gen.writelines('%svoid print(const %s& in){\n' % (inline, type))
    for field in types[type]["fields"]:
        tag = (', ' + field["attributes"]["tag"] + '()') if "tag" in field["attributes"] else ''
        gen.writelines('    print(in.%s%s;)\n' % (field["name"], tag))
    gen.writelines('}\n\n')

gen.close()



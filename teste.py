import os

abspath = os.path.abspath(__file__)
dname = os.path.dirname(abspath)

dependencies = [ dname + "\dependencies\pyserial\setup.py",
                 dname + "\dependencies\mysql_connector\setup.py" ]

print(dependencies)

def exec_full(filepath):
    global_namespace = {
        "__file__": filepath,
        "__name__": "__main__",
    }
    with open(filepath, 'rb') as file:
        exec(compile(file.read(), filepath, 'exec'), global_namespace)


#exec_full(dependencies[0])

#exec_full(dependencies[1])

dependencies[0] install

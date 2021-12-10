#! /usr/bin/python3

import mimetypes
import os

def delete_binary_file(target_file, dir_name):
    isBinary = False
    isSkipped = False
    type_, encodeing = mimetypes.guess_type(target_file)
    if type_ == None:
        isBinary = True
        if  target_file.endswith(".dat"):
            print(f"Skipping {os.path.join(dir_name, target_file)}")
            isSkipped = True
            return isBinary, isSkipped
        os.remove( os.path.join(dir_name, target_file) )
        print( 'deleted: ', os.path.join(dir_name, target_file) )
    return isBinary, isSkipped


if __name__ == '__main__':
    root_dir = os.path.dirname( os.path.abspath(__file__) )
    print('working from:', root_dir)
    existsBinary = False

    deleted = 0
    skipped = 0

    for root, dirs, files in os.walk(root_dir, topdown=True):
        # print(f">>> {root}, {dirs}, {files}")
        if '.git' in root or '.vscode' in root:
            continue # skip hidden directories
        for file in files:

            # the following statement has a bug in it.
            # existsBinary = existsBinary or delete_binary_file(file, root)

            # this one will work, first operand will always be executed
            # existsBinary = delete_binary_file(file, root) or existsBinary

            # refactory
            binary_result, skip_result = delete_binary_file(file, root)
            if binary_result and not skip_result: # not realying on skip_result to be evaluated
                deleted += 1
            if skip_result:
                skipped += 1
            existsBinary = existsBinary or binary_result # not relying on binary_result to be evaluated

    print(f'{deleted} deleted, {skipped} skipped.')
    if not existsBinary:
        print('No binaries exist.')
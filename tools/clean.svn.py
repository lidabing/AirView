import os, stat;

root_dir = 'C:/github/chromium-36.0.1985.125';

def walk(path):
     for item in os.listdir(path):
         subpath = os.path.join(path, item);
         mode = os.stat(subpath)[stat.ST_MODE];
         
         if stat.S_ISDIR(mode):
             if item==".svn":
                 print "Clean %s ..." % subpath;
                 print "%d deleted!" % purge(subpath);
             else:
                 walk(subpath);

def purge(path):
     count = 0;
     for item in os.listdir(path):
         subpath = os.path.join(path, item);
         mode = os.stat(subpath)[stat.ST_MODE];
         if stat.S_ISDIR(mode):
             count += purge(subpath);
         else:
             os.chmod(subpath, stat.S_IREAD|stat.S_IWRITE);
             os.unlink(subpath);
             count += 1;
     os.rmdir(path);
     count += 1;
     return count;
                      
     

if __name__=='__main__':
     walk(root_dir);
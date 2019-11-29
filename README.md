# RS003-kompozitor
Kompozitor

## Note on running with CLion
Since Qt uses its own CMake prefix, to run this with CLion, go to `Settings > Build, Execution, Deployment > CMake`
and set the **CMake options** to
```
-DCMAKE_PREFIX_PATH=/PATH/TO/YOUR/Qt/5.12.6/gcc_64/lib/cmake/
```
For example, the usual path for Unix is this:
```
-DCMAKE_PREFIX_PATH=~/Qt/5.12.6/gcc_64/lib/cmake/
``` 

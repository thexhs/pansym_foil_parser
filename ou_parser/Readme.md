Some helpfull function for work with PANSYM input and output file (*.in/*.ou)

Get_Cp.ipynb
This function designed to extract pressure distribution from PANSYM ou files to Excel sheet

|Function|Description|
|---:|:---|
|`Split_Section_AoA()`|return content of file as Python dictionary. AoA as key, List of string as all data related for this AoA value|
|`Get_AoA_by_index()`|return list of string for selected item from AoA dictionary by index (using Python 3.6 ordered dictionary)|
|`Split_AoA_IBLOCK()`|return dictionary. Section number as key, all section related data as List of string|
|`get_Cp()`|return list of float - X,Y,Z coordinates and Cp value for selected section|
|`XLSX_Cp_Dump()`|write all sections data for selected AoA in Excel *.xslx file|

Split_IN.ipynb
Some function for parsing PANSYM input file and extract useful information from it. Not all options from PANSYM input file specification was implement, but most useful was.

|Function|Description|
|---:|:---|
|`Read_file()`|return file content as list of string|
|`Read_block()`|return List of string contain sub-block starting at prescribed line, define type of sub-block and call necessary reading function|
|`Control_Line()`|return a list of int with control numbers from string passed in|
|`Read_Airfoil()`|calculate linecount via control line and return airfoil as list of string|
|`Read_Body()`|calculate linecount via control line and return fuselage as list of string|
|`Read_Wing()`|calculate linecount via control line and return wing as list of string|
|`Read_Nacelle()`|calculate linecount via control line and return jet nacelle (circular) as list of string|
|`Read_Jet()`|calculate linecount via control line and return jet as list of string|
|`Str2Coords()`|return list of float from input string|
|`Block2Coords()`|return list of float from input list of string|
|`Airfoil_plot()`|plot airfoil from block, e.g. from `Read_Airfoil` output|
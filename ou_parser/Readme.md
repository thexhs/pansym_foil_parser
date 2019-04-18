Some helpfull function for work with PANSYM output file (*.ou)

Split_Section_AoA() - return content of file as Python dictionary. AoA as key, List of string as all data related for this AoA value

Get_AoA_by_index() - return list of string for selected item from AoA dictionary by index (using Python 3.6 ordered dictionary)

Split_AoA_IBLOCK() - return dictionary. Section number as key, all section related data as List of string

get_Cp() - return list of float - X,Y,Z coordinates and Cp value for selected section

XLSX_Cp_Dump() - write all sections data for selected AoA in Excel *.xslx file
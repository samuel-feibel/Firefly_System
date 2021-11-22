fileNames =  {'ff','G','H','hh','Phi'};
varNames = {'f','G_jac','H_jac','h','Phi'};


for i=1:length(fileNames)
    fid  = fopen(['INS/' fileNames{i} '.c'],'r');
    f=fread(fid,'*char')';
    fclose(fid);

    f = ['float ' f];
    f = strrep(f,'][',',');
    f = strrep(f,'[','(');
    f = strrep(f,']',')');
    f = strrep(f,'\n','sam');
    f = regexprep(f,'[\n\r]+  t','\n float t');
    f = strrep(f,'magVec0Sym1','magVec0(0)');
    f = strrep(f,'magVec0Sym2','magVec0(1)');
    f = strrep(f,'magVec0Sym3','magVec0(2)');
    f = strrep(f,'gravVec0Sym1','gravVec0(0)');
    f = strrep(f,'gravVec0Sym2','gravVec0(1)');
    f = strrep(f,'gravVec0Sym3','gravVec0(2)');

    f = strrep(f,'A0',varNames{i});

    fid  = fopen(['INS/edited_' fileNames{i} '.c'],'w');
    fprintf(fid,'%s',f);
    fclose(fid);
end
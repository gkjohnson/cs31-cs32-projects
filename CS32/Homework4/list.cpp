void listAllAuxiliary(string path, const File* f)
{
	cout<<path+"/"+f->name()<<endl;
	for(int i=0;f->files()!=NULL&&i<(f->files()->size());i++){
		listAllAuxiliary(path+"/"+f->name(),(f->files()->at(i)));
	}
}
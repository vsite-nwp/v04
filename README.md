#### vježba 4	

Napišite program kojim pomičete brod po prozoru. Kao brod neka vam posluži _static_ sa tekstom "x". 
* klik lijevom tipkom miša postavlja trenutnu poziciju "broda"
* strelicama se "brod" vozi po prozoru
* brod ne smije izaći izvan prozora
* ako je pritisnuta i _Ctrl_ tipka "brod" se kreće brže (u većim koracima)
* dok se "brod" miče ima crni rub, inače nema


Uputstva:
* dodajte u baznu klasu vsite::nwp::window obradu poruka WM_LBUTTONDOWN, WM_KEYDOWN, WM_KEYUP
* za micanje prozora možete koristiti funkciju [SetWindowPos](https://msdn.microsoft.com/en-us/library/windows/desktop/ms633545%28v=vs.85%29.aspx) (koristeći SWP_NOSIZE i SWP_NOZORDER) 
* veličinu prozora možete saznati sa [GetClientRect](https://msdn.microsoft.com/en-us/library/windows/desktop/ms633503%28v=vs.85%29.aspx)
* nakon što promijenite stil prozoru (da bi se pokazao/sakrio rub), ponovno iscrtavanje cijelog prozora forsirate sa SetWindowPos koristeći flag SWP_FRAMECHANGED (uz SWP_NOMOVE, SWP_NOSIZE, SWP_NOZORDER)

![ship](/screenshot.jpg?raw=true)

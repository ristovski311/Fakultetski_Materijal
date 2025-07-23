using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace OOProj.WindowsAplikacija
{
    public class Student
    {
        string _ime;
        string _prezime;
        int _index;

        public Student()
        {
            _ime = String.Empty;
            _prezime = String.Empty;
            _index = 0;
        }

        public Student(String ime, String p, int i)
        {
            _ime = ime;
            _prezime = p;
            _index = i;
        }

        public String Ime
        {
            get 
            {
                return _ime;
            
            } 

            set
            {
                _ime = value; 
            }
        }

        public String Prezime
        {
            get { return _prezime;}

            set { _prezime = value; }
        }

        public int Index
        {
            get { return _index; }
            set
            {
                _index = value;
            }   
        }

        public String PrikaziPodatke()
        {
            return "Ime: " + _ime+" Prezime:" + _prezime + " Index: " + _index;
        }

    }
}

using UnityEngine;
using System.Collections;
using System.IO.Ports;

public class Serial_COM : MonoBehaviour
{

    SerialPort serial = new SerialPort("\\\\.\\COM11", 9600); 
    


    void Start()
    {
        serial.Open();
        serial.ReadTimeout = 1;
    }

    char[] array=new char[7];
    string read;
    void Update()
    {
        {
            for (int i = 0; i < 7; i++)
                array[i] = '0';


            if (Input.GetKey(KeyCode.UpArrow))
            {
                array[0] = '1';
                array[1] = '1';
            }
            else if (Input.GetKey(KeyCode.DownArrow))
            {
                array[0] = '2';
                array[1] = '2';
            }
            else
            {
                array[0] = '0';
                array[1] = '0';
            }
            if (Input.GetKey(KeyCode.LeftArrow))
            {
                array[2] = 'l';
            }
            else if (Input.GetKey(KeyCode.RightArrow))
            {
                array[2] = 'r';
            }
            else
                array[2] = '0';




            //array[3] = ' ';

            if (Input.GetKey(KeyCode.K))
            {
                array[3] = '0';
                array[4] = 'x';
                array[5] = ' ';

            }
            else if (Input.GetKey(KeyCode.L))
            {
                array[3] = '0';
                array[4] = 'w';
                array[5] = ' ';

            }
            if (Input.GetKey(KeyCode.I))
            {
                array[3] = '0';
                array[5] = 'z';
                array[6] = ' ';

            }
            else if (Input.GetKey(KeyCode.M))
            {
                array[3] = '0';
                array[5] = 'y';
                array[6] = ' ';
            }
            if (Input.GetKey(KeyCode.Space))
            {
                array[0] = 's';
            }
            if (Input.GetKey(KeyCode.P))
            {
                array[0] = 'p';
            } if (Input.GetKey(KeyCode.T))
            {
                array[0] = 't';
            }

            string s = new string(array);
            serial.Write(s+' ');
           // if (serial.BytesToRead > 1)
            //{
                
                read = serial.ReadLine();
            //}
        }


serial.BaseStream.Flush(); //clear serial
        //}
    }

    void OnGUI()
    {
        string newString = "Connected: " + read;
        GUI.Label(new Rect(10, 10, 300, 100), newString); 
        //Instantiate(car, transform.position + (transform.forward * 2), transform.rotation);

    }
}
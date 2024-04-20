import PySimpleGUI as sg
import math
import csvpy
import time





toprow = ['Price', 'Condition','Brand', 'Model', 'Year', 'Type', 'Color' ]
rows = []

tb1 = sg.Table(values=rows, headings=toprow,
               auto_size_columns=True,
               display_row_numbers=False,
               justification='center', key='-TABLE-',
               selected_row_colors='red on yellow',
               enable_events=True,
               expand_x=True,
               expand_y=True,
               enable_click_events=True)

layout = [[sg.Text('Poland Car')],
          [sg.Text('Price'), sg.Combo([1, 2, 3, 4, 5, 6], size=(20, 10), default_value=5, key='price')],
          [sg.Text('Brand'), sg.Combo([1, 2, 3, 4, 5, 6], size=(20, 10), default_value=1, key='brand')],
          [sg.Text('Model'), sg.Combo([1, 2, 3, 4, 5, 6], size=(20, 10), default_value=2, key='model')],
          [sg.Text('Production Year'), sg.Combo([1, 2, 3, 4, 5, 6], size=(20, 10), default_value=3, key='year')],
          [sg.Text('Type'), sg.Combo([1, 2, 3, 4, 5, 6], size=(20, 10), default_value=4, key='type')],
          [sg.Text('Color'), sg.Combo([1, 2, 3, 4, 5, 6], size=(20, 10), default_value=6, key='color')],
          [sg.Text('After Year'), sg.InputText(key='afteryear',default_text=1900) ],
          [sg.Text('Condition'), sg.Combo(['New','Used'], size=(20, 10), default_value='New', key='cond')],
          [sg.Text(text_color='black', key='out')],
          [sg.Button('QuickSort'), sg.Button('HeapSort'), sg.Button('QuickSort rand'), sg.Button('Clear')],
          [tb1],

          [sg.Button('Set Order'), sg.Button('Set Filter'), sg.Button('Unset Filter'), sg.Button('Cancel')]]

# Create the Window
window = sg.Window('Window Title', layout, finalize=True)

window.maximize()


m = csvpy.CSV("new.csv",208034)
m.get_file()


while True:
    event, values = window.read()
    if event == sg.WIN_CLOSED or event == 'Cancel':  # if user closes window or clicks cancel
        break
    if event == 'Set Order':
        order = [values['price'], values['brand'], values['year'], values['model'], values['type'], values['color']]

        if set(order) != {1, 2, 3, 4, 5, 6}:
            result = 'wrong order'
        else:
            order_dict = {
                values['price']: ['price',0],
                values['brand']: ['brand',1],
                values['model']: ['year', 2],
                values['year']: ['model',3],
                values['type']: ['type',4],
                values['color']: ['color',5]
            }
            result = ' '.join(
                order_dict[i + 1][0] for i in range(6)
            )
            m.set_order( [ order_dict[i+1][1] for i in range(6)])

        window['out'].update(value=result)
    if( event == 'QuickSort' ):
        t1 = time.time()
        m.sort_by(1)
        t2 = time.time()
        temp = m.print_file()
        result = [
            temp[i].split(',') for i in range(1000)
        ]
        tb1.update(values=result)
        window['out'].update(value='quicksort cpu time is {}'.format(t2-t1))
    if (event == 'QuickSort rand'):
        t1 = time.time()
        m.sort_by(2)
        t2 = time.time()
        temp = m.print_file()
        result = [
            temp[i].split(',') for i in range(1000)
        ]
        tb1.update(values=result)
        window['out'].update(value='quicksort rand cpu time is {}'.format(t2 - t1))

    if (event == 'HeapSort'):
        t1 = time.time()
        m.sort_by(0)
        t2 = time.time()
        temp = m.print_file()
        result = [
            temp[i].split(',') for i in range(1000)
        ]
        tb1.update(values=result)
        window['out'].update(value='heapsort cpu time is {}'.format(t2 - t1))
    if event == 'Clear':
        tb1.update(values=[])
    if event == 'Cancel':
        window.close()
    if event == 'Set Filter' :
        if values['cond'] == 'Used':
            cond = 2
        else :
            cond = 1
        print()
        m.set_filter( cond, int(values['afteryear']))
        window['out'].update(value='filter set with cond = {} year = {}'.format(values['cond'], values['afteryear'] ))
    if event == 'Unset Filter' :
        m.set_filter( 0, 1900 )
        window['out'].update(value='filter unset')

    # if event == 'price':
    #    window['price'].update(val=values['price'])
window.close()

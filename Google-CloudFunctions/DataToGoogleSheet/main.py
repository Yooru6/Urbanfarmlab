import base64
from apiclient import discovery
import json

def hello_pubsub(event, context):

     sheets = discovery.build('sheets', 'v4')

     SPREADSHEETID = '1LNlukogdfW5PF7CSXnQF3FaekA6Pp6QUROna86muksg'

     #Decode data
     data2sheet=base64.b64decode(event['data']).decode('utf-8')
     data2sheetJSON = json.loads(data2sheet)

     #Values from the event
     dataValues=[str(event['attributes']['published_at'])]+list(data2sheetJSON.values())
     dataKeys=list(data2sheetJSON.keys())

     mySpreadsheets = sheets.spreadsheets().get(spreadsheetId=SPREADSHEETID).execute()
     worksheet_name = 'Greenhouse!'#name of sheet where data will be written
     cell_range_insert = 'B2' #First column for data
     
     #prepare values for append by putting them on list
     values = [dataValues]
     value_range_body = {'majorDimension': 'ROWS','values': values}

     #Append values to spreadsheet 
     #.update writes data to defined location(can overwrite) 
     #.append just add values end of data
     sheets.spreadsheets().values().append(
     spreadsheetId=SPREADSHEETID,
     valueInputOption='USER_ENTERED',
     range=worksheet_name + cell_range_insert,
     body=value_range_body
     ).execute() 
     




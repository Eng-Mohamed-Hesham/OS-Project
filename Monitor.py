#Importing the required libraries
import psutil           
import datetime
import pandas as pd     

#Creating lists to store the corresponding information
cpu_usage= []
memory_usage = []
memory_usage_percentage = []
pids = []
name = [] 
status =[]
create_time =[]
threads =[]

#Getting application process information using psutil
for process in psutil.process_iter():
    pids.append(process.pid)
    name.append(process.name())

    cpu_usage.append(process.cpu_percent(interval=1)/psutil.cpu_count())
    memory_usage.append(round(process.memory_info().rss/(1024*1024),2))
    memory_usage_percentage.append(round(process.memory_percent(),2))
    create_time.append(datetime.datetime.fromtimestamp(
                        process.create_time()).strftime("%Y%m%d - %H:%M:%S"))
    status.append(process.status())
    threads.append(process.num_threads())
    
#Saving the process information in a python dictionary
data = {"PIds":pids,
        "Name": name,
        "CPU":cpu_usage,
        "Memory Usages(MB)":memory_usage,
        "Memory Percentage(%)": memory_usage_percentage,
        "Status": status,
        "Created Time": create_time,
        "Threads": threads,
        }
        
#Converting the dictionary into Pandas DataFrame
process_df = pd.DataFrame(data)

#Setting the index to pids
process_df =process_df.set_index("PIds")

#sorting the process 
process_df =process_df.sort_values(by='Memory Usages(MB)', ascending=False)

#Adding MB at the end of memory
process_df["Memory Usages(MB)"] = process_df["Memory Usages(MB)"].astype(str) + " MB"

print(process_df)

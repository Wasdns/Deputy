# Assume we are in the directory of Deputy

# Download the project
sudo apt-get install git
git clone https://github.com/Wasdns/Deputy-generator.git 

# Generate input_data.txt
cd Deputy-generator/src
sudo ./cleanup.sh
sudo ./compile.sh
./main

# move to Deputy directory
cp -r input_data.txt ../Project/

# enter to Deputy directory
cd ../Project/

# Generate target program
sudo ./compile.sh
./main

# Cleanup the environment
sudo ./cleanup.sh
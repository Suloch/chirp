from django.shortcuts import render
from django.http import JsonResponse
import subprocess

def run(request):
    if request.method == 'POST':
        if 'program' in request.POST:
            program = request.POST.get('program')
            file = open('./program.rocks', 'w+')
            file.write(program)
            file.close()
            args = ('chirp', 'program.rocks')
            popen = subprocess.Popen(args, stdout=subprocess.PIPE)
            popen.wait()
            output = popen.stdout.read()
            output = output.decode()
            return JsonResponse({'status': 'successful', 'output' : str(output)})
        else:
            return JsonResponse({'status' : 'failed'})
    else:
        return render(request, 'main/get_program.html')

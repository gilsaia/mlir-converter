import torch
from torch import nn
import torch_mlir

class SimpleNet(nn.Module):
    def __init__(self):
        super().__init__()
        self.fc1=nn.Linear(32,128)
        self.act1=nn.ReLU()
        self.fc2=nn.Linear(128,16)
    
    def forward(self,x):
        x=self.fc1(x)
        x=self.act1(x)
        x=self.fc2(x)
        return x

def GetPredefinedModel(ModelName='simple-net'):
    if ModelName=='simple-net':
        model=SimpleNet()
        module=torch_mlir.compile(model,torch.ones(1,32),output_type='torch')
        return str(module)
    else:
        raise NotImplementedError("not defined model")
    
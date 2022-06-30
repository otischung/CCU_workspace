from dataloader import *
from image_show import *
from model import *
from train_model import *
from visualize_model import *


def main():
    if os.path.isdir("./AI_CUP") is False:
        if os.path.isfile("./Download_Dataset.sh"):
            os.system("./Download_Dataset.sh")
        else:
            print(f"{Bcolors.FAIL}Error, cannot download dataset.{Bcolors.ENDC}", file=sys.stderr)
            quit(1)
    # if os.path.isdir(model_dir) is False:
    #     os.mkdir(model_dir)
    if os.path.isdir(loss_dir) is False:
        os.mkdir(loss_dir)
    if os.path.isdir(test_dir) is False:
        os.mkdir(test_dir)

    # 資料集載入 =======================================================================
    dataloaders, dataset_sizes, class_names = my_dataloader()
    # 資料集載入 =======================================================================

    # 設定 CUDA 環境 =======================================================================
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    print(f"Using device {device}\n")
    # 設定 CUDA 環境 =======================================================================

    # Get a batch of training data
    inputs, classes = next(iter(dataloaders['train']))

    # Make a grid from batch
    out = torchvision.utils.make_grid(inputs)

    # imshow(out, title=[class_names[x] for x in classes])

    # model =======================================================================
    # ===== ↓ Begin AlexNet ↓ =====
    # ===== ↓ DON'T NEED ANYMORE ↓ =====
    # model_ft = MyCNN(num_classes=219)
    # pretrained_dict = load_state_dict_from_url(
    #     'https://download.pytorch.org/models/alexnet-owt-4df8aa71.pth',
    #     model_dir=model_dir,
    #     progress=True
    # )
    # ===== ↑ DON'T NEED ANYMORE ↑ =====

    # download to "~/.cache/torch/hub/checkpoints/"
    # model_ft = alexnet(pretrained=True)
    # model_ft.classifier[6] = nn.Linear(in_features=4096, out_features=219, bias=True)
    # model_ft.classifier = nn.Sequential(*[model_ft.classifier[i] for i in range(4)])  # select range

    # ===== ↓ DO NOT USE THESE FUNCTIONS ↓ =====
    # model_ft.features.append(nn.Conv2d(in_channels=256, out_channels=512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1)))
    # model_ft.features.append(nn.ReLU(inplace=True))
    # model_ft.features.append(nn.MaxPool2d(kernel_size=3, stride=1, padding=0))
    # model_ft.features.append(nn.Conv2d(in_channels=512, out_channels=256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1)))
    # model_ft.features.append(nn.ReLU(inplace=True))
    # model_ft.features.append(nn.MaxPool2d(kernel_size=3, stride=1, padding=0))
    # model_ft.classifier[1] = nn.Linear(in_features=1024 * 6 * 6, out_features=4096, bias=False)
    # ===== ↑ DO NOT USE THESE FUNCTIONS ↑ =====

    # model_ft.classifier.append(nn.Softmax(dim=1))

    # ===== ↑ End AlexNet ↑ =====

    # ===== ↓ Begin ResNet ↓ =====

    # model_ft = resnet34(pretrained=True)
    # model_ft = resnet50(pretrained=True)
    # model_ft = resnet101(pretrained=True)
    # model_ft = resnext50_32x4d(pretrained=True)
    # model_ft = resnext101_32x8d(pretrained=True)
    # model_ft.fc = nn.Sequential(
    #     model_ft.fc,
    #     nn.ReLU(inplace=True),
    #     nn.Linear(in_features=1000, out_features=219, bias=True)
    # )

    # ===== ↑ End ResNet ↑ =====

    # ===== ↓ Begin VGG ↓ =====

    # model_ft = vgg11(pretrained=True)
    # model_ft = vgg16(pretrained=True)
    # model_ft = vgg19(pretrained=True)
    # model_ft.classifier[6] = nn.Linear(in_features=4096, out_features=219, bias=True)

    # ===== ↑ End VGG ↑ =====

    # ===== ↓ Begin GoogleNet ↓ =====

    model_ft = googlenet(pretrained=True)
    model_ft.fc = nn.Sequential(
        model_ft.fc,
        nn.ReLU(inplace=True),
        nn.Linear(in_features=1000, out_features=219, bias=True)
    )

    # ===== ↑ End GoogleNet ↑ =====

    # model_dict = model_ft.state_dict()
    # 1. filter out unnecessary keys
    # pretrained_dict = {k: v for k, v in pretrained_dict.items() if k in model_dict}
    # 2. overwrite entries in the existing state dict
    # model_dict.update(pretrained_dict)
    # 3. load the new state dict
    # model_ft.load_state_dict(model_dict)

    print(model_ft)
    # for k, v in model_ft.items():
    #     print(f"{k}: {len(v)}")
    # quit(0)
    model_ft = model_ft.to(device)
    # model =======================================================================

    parameter_count = sum(p.numel() for p in model_ft.parameters() if p.requires_grad)
    print(f"#parameters:{parameter_count}")
    print(f"batch_size:{batch_size}")

    criterion = nn.CrossEntropyLoss()

    # Observe that all parameters are being optimized
    # optimizer_ft = optim.SGD(model_ft.parameters(), lr=lr, momentum=momentum)
    optimizer_ft = optim.AdamW(model_ft.parameters(), lr=lr, weight_decay=weight_decay)

    # Decay LR by a factor of 0.1 every 7 epochs
    # exp_lr_scheduler = lr_scheduler.StepLR(optimizer_ft, step_size=7, gamma=0.1)
    exp_lr_scheduler = 0

    model_ft = train_model(
        model_ft,
        criterion,
        device,
        dataloaders,
        dataset_sizes,
        optimizer_ft,
        exp_lr_scheduler,
        num_epochs=num_epochs
    )

    visualize_model(model_ft, device, dataloaders, class_names)


if __name__ == '__main__':
    main()

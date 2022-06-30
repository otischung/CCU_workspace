from import_package import *


def imshow(inp, title=None):
    # plt.ion()  # interactive mode
    """Imshow for Tensor."""
    inp = inp.numpy().transpose((1, 2, 0))
    mean = np.array([0.485, 0.456, 0.406])
    std = np.array([0.229, 0.224, 0.225])

    # 原先Normalize是對每個channel個別做 減去mean, 再除上std
    inp1 = std * inp + mean

    plt.imshow(inp)

    if title is not None:
        plt.title(title)
    plt.pause(0.001)  # pause a bit so that plots are updated
    print("This is the original pictures.\nPress Enter to continue.", file=sys.stderr)
    input()
    plt.close()
    plt.imshow(inp1)
    if title is not None:
        plt.title(title)
    plt.pause(0.001)  # pause a bit so that plots are updated
    print("This is the pictures after normalization.\nPress Enter to continue.", file=sys.stderr)
    input()
    plt.close()

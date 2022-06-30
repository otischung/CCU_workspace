from import_package import *


def train_model(model, criterion, device, dataloaders, dataset_sizes, optimizer, scheduler, num_epochs=25):
    since = time.time()

    best_model_wts = copy.deepcopy(model.state_dict())
    best_acc = 0.0
    best_loss = 2147483647
    early_stop_cnt = 0
    train_loss, valid_loss = [], []
    train_acc, valid_acc = [], []

    try:
        for epoch in range(num_epochs):
            print(f"Epoch {epoch + 1}/{num_epochs}", file=sys.stderr)
            print('-' * 10, file=sys.stderr)

            # Each epoch has a training and validation phase
            for phase in ['train', 'val']:
                if phase == 'train':
                    model.train()  # Set model to training mode
                else:
                    model.eval()  # Set model to evaluate mode

                running_loss = 0.0
                running_corrects = 0

                # Iterate over data.
                for inputs, labels in tqdm(dataloaders[phase]):
                    inputs = inputs.to(device)
                    labels = labels.to(device)

                    # forward
                    # track history if only in train
                    with torch.set_grad_enabled(phase == 'train'):
                        outputs = model(inputs)
                        _, preds = torch.max(outputs, 1)
                        loss = criterion(outputs, labels)

                        # backward + optimize only if in training phase
                        if phase == 'train':
                            # zero the parameter gradients
                            optimizer.zero_grad()
                            loss.backward()
                            optimizer.step()

                    # statistics
                    running_loss += loss.item() * inputs.size(0)
                    running_corrects += torch.sum(preds == labels.data)
                # if phase == 'train':
                #     scheduler.step()

                epoch_loss = running_loss / dataset_sizes[phase]
                epoch_acc = running_corrects.double() / dataset_sizes[phase]

                if phase == 'train':
                    train_loss.append(epoch_loss)
                    train_acc.append(epoch_acc)
                else:
                    valid_loss.append(epoch_loss)
                    valid_acc.append(epoch_acc)

                print(f"{Bcolors.OKBLUE}{phase} Loss: {epoch_loss:.4f}, Acc: {epoch_acc:.4f}{Bcolors.ENDC}", file=sys.stderr)
            # deep copy the model
            if phase == 'val' and best_loss > epoch_loss:
                best_loss = epoch_loss
                best_acc = epoch_acc
                early_stop_cnt = 0
                best_model_wts = copy.deepcopy(model.state_dict())
                print(f"{Bcolors.WARNING}Saving model with Loss: {epoch_loss:.4f} and Acc: {epoch_acc:.4f}{Bcolors.ENDC}", file=sys.stderr)
            elif early_stop_cnt >= early_stop:
                print(f"{Bcolors.FAIL}The model is not improved after {early_stop} step, stop training.", file=sys.stderr)
                break
            else:
                early_stop_cnt += 1
            # if phase == 'val' and best_acc < epoch_acc:
            #     best_acc = epoch_acc
            #     best_model_wts = copy.deepcopy(model.state_dict())

    except KeyboardInterrupt:
        print(f"{Bcolors.FAIL}Received SIGINT, stop training.{Bcolors.ENDC}", file=sys.stderr)

    plt.figure(0)
    # plt.plot(range(1, num_epochs + 1, 1), np.array(train_loss), 'r-', label="train loss")  # relative global step
    plt.plot(range(1, len(train_loss) + 1, 1), np.array(train_loss), 'r-', label="train loss")  # relative global step
    plt.xlabel('epoch')
    plt.ylabel('loss')
    plt.legend()
    plt.savefig(f"{loss_dir}/train_loss.png")

    plt.figure(1)
    # plt.plot(range(1, num_epochs + 1, 1), np.array(valid_loss), 'b-', label="eval loss")  # --evaluate_during_training True 在啟用eval
    plt.plot(range(1, len(valid_loss) + 1, 1), np.array(valid_loss), 'b-', label="eval loss")  # --evaluate_during_training True 在啟用eval
    plt.xlabel('epoch')
    plt.ylabel('loss')
    plt.legend()
    plt.savefig(f"{loss_dir}/eval_loss.png")

    time_elapsed = time.time() - since
    print(f"Training complete in {(time_elapsed // 60):.0f}m {(time_elapsed % 60):.0f}s")
    print(f"Best val Acc: {best_acc:4f}")

    # load best model weights
    model.load_state_dict(best_model_wts)
    # torch.save(model.state_dict(),"model.pt")
    return model

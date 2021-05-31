from flask import Flask, render_template, request

app = Flask(__name__)


@app.route("/")
def home():
    return "<h1>Hello world</h1>"


@app.route("/demo_template", methods=["GET"])
def demo_temp():
    return render_template("test.html", title="這是一個template的demo")


@app.route("/greet", methods=["GET"])
def greet():
    user_name = request.args.get('name')
    return render_template("greet.html", name=user_name)


@app.route("/form", methods=["GET"])
def form():
    return render_template('form.html')  # This will call login function.


@app.route("/login", methods=["POST"])
def login():
    user_name = request.form.get('user')
    pwd = request.form.get('passwd')
    return render_template("login_demo.html", name=user_name, password=pwd)


app.run(port=1234)

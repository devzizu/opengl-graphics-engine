# Computer Graphics Engine - Solar System

The goal of this assignment is to develop a mini scene graph based 3D engine and provide usage
examples that show its potential. The assignment is split in four phases and each phase has its report and code for the **engine** and **generator**. Here you can see the project [assignment paper](https://github.com/devzizu/Computer-Graphics/blob/master/2020/assignment.CG.eng.PDF).

## Development process - four phases

### **Phase 1** - *Algorithms for Graphical primitives* 
[(phase 1 report)](https://github.com/devzizu/Computer-Graphics/blob/master/2020/Fase-1/Relat%C3%B3rio_Fase-1.pdf)
- We built two applications using C++: the **generator** whose goal was to generate vertices for different models like planes, boxes, spheres and cones (and its measures - x y z). After running the program with the appropriate arguments, files called <model>.3d are generated, for example:

Example: [**cone.3d**](https://github.com/devzizu/Computer-Graphics/blob/master/2020/Fase-1/examples/Model-Read-Tests/cone.3d) (3601 lines of vertices)

```c
3600
0 0 0
0.618034 0 1.90211
...

```

After that, the engine is able to load this files specified in the **xml** scene configuration files:
```xml
<scene>
    <model file = "cone.3d"/>
</scene>
```
And the model is displayed in the screen using the OpenGL API. Although this is a very simple example, models can get much bigger and complex, each phase we increase the functionalities of this applications.

### **Phase 2** - *Apply hierarchical Geometric Transforms* 
[(phase 2 report)](https://github.com/devzizu/Computer-Graphics/blob/master/2020/Fase-2/Relat%C3%B3rio_Fase-2.pdf)
   - Now the **xml scenes** have an hierarchical structure meaning that they are defined as a tree where each node contains a set of geometric transforms (translate, rotate and scale) and optionally a set of models. Each node can also have children nodes. So, basically we only work on the **engine**, adding memory structures, features in the xml reader and OpenGL code to render the scene in order.

```xml
<scene>
    <group>
        <!-- Planet -->
        <translate X = "10" />
        <group>
            <scale X="167.3" Y="167.3" Z="167.3"/>
            <group>
                <models>
                    <model file="sphere.3d" />
                </models>
            </group>
            <!-- Moon -->
                 ...
        </group>
    </group>
</scene> 

```

### **Phase 3** - *Curves, Cubic Surfaces and Vertex buffer objects (VBOs)* 
[(phase 3 report)](https://github.com/devzizu/Computer-Graphics/blob/master/2020/Fase-3/Relat%C3%B3rio_Fase-3.pdf)
   
  - Now the **generator** application creates a <ins>new type of model</ins> based on [*Bézier patches*](https://pt.wikipedia.org/wiki/Superf%C3%ADcies_de_B%C3%A9zier) applying Bézier rules for the defined **control points** and **tesselation level**.

Now we run the model like this:

```bash
generator bezier-patch <patch-file> <tesselation> <output-file-name>
```

For example, running [teapot.patch](https://github.com/devzizu/Computer-Graphics/blob/master/2020/Fase-3/examples/Models.patch/teapot.patch) file with tesselation level of 10:

```bash
generator bezier-patch teapot.patch 10 teapot.3d
```
...and the corresponding **teapot.3d** file is generated with all the vertices that make the model triangles.

- **Rotate** and **Translate** elements have been extended now, for example, to animate the planets moving around its orbit we defined a set of points to define a [Catmull-Rom](https://en.wikipedia.org/wiki/Centripetal_Catmull%E2%80%93Rom_spline) cubic curve and provided the number of seconds to run the whole curve.

- Finally, VBOs were added as opposed to immediate mode used in the previous phases.

### **Phase 4** - *Normals and Texture Coordinates* 
[(phase 4 report)](https://github.com/devzizu/Computer-Graphics/blob/master/2020/Fase-4/Relat%C3%B3rio_Fase-4.pdf)
   - (see assignment and reports for more information)

### Members / Maintainers


|      Name     | Number |
|---------------|--------|
| [João Azevedo](https://github.com/devzizu)   | A85227 |
| [Pedro Machado](https://github.com/PedroFCM) | A83719 |
| [Paulo Araújo](https://github.com/paulob122) | A85729 |
| [Paulo Lima](https://github.com/paulolima18) | A89983 |

<br>

>**University of Minho, Software Engineering (3rd year)**.

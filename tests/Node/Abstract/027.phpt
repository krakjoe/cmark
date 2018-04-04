--TEST--
CommonMark\Node accept
--FILE--
<?php
$visited = [];

$doc = new \CommonMark\Node\Document;

$doc->accept(new class implements \CommonMark\Interfaces\IVisitor {
	public function enter(\CommonMark\Interfaces\IVisitable $node) {}
	public function leave(\CommonMark\Interfaces\IVisitable $node) {}
});

var_dump($visited);

$visited = [];

$para = new \CommonMark\Node\Paragraph;

$doc->appendChild($para);
$para->appendChild(
	new \CommonMark\Node\Text());

$doc->accept(new class($visited) implements \CommonMark\Interfaces\IVisitor {
	public function __construct(array &$visited) {
		$this->visited = &$visited;
	}

	public function enter(\CommonMark\Interfaces\IVisitable $node) {
		$this->visited[] = $node;
	}

	public function leave(\CommonMark\Interfaces\IVisitable $node) {}
});

var_dump($visited);

$visited = [];

$doc = new \CommonMark\Node\Document;
$doc->appendChild(new \CommonMark\Node\Paragraph);

$doc->accept(new class($visited) implements \CommonMark\Interfaces\IVisitor {
	public function __construct(array &$visited) {
		$this->visited = &$visited;
	}

	public function enter(\CommonMark\Interfaces\IVisitable $node) {
		$this->visited[] = 
			get_class($node);

		return \CommonMark\Interfaces\IVisitor::Leave;
	}
	
	public function leave(\CommonMark\Interfaces\IVisitable $node) {}
});

var_dump($visited);

$visited = [];

$doc->accept(new class($visited) implements \CommonMark\Interfaces\IVisitor {
	public function __construct(array &$visited) {
		$this->visited = &$visited;
	}

	public function enter(\CommonMark\Interfaces\IVisitable $node) {
		$this->visited[] = 
			get_class($node);

		return $node->lastChild;
	}
	
	public function leave(\CommonMark\Interfaces\IVisitable $node) {}
});

var_dump($visited);

$visited = [];

$doc = CommonMark\Parse(<<<EOD
  * item 1
  * item 2
  * item 3
EOD
);

$doc->accept(new class($visited) implements \CommonMark\Interfaces\IVisitor {
	public function __construct(array &$visited) {
		$this->visited = &$visited;
	}

	public function enter(\CommonMark\Interfaces\IVisitable $node) {
		if ($node instanceof \CommonMark\Node\Document) {
			return;
		}

		$this->visited[] = get_class($node);

		if ($node instanceof \CommonMark\Node\Item)
			/* skip all Item child nodes */
			return [
				\CommonMark\Interfaces\IVisitor::Enter 
					=> $node->firstChild->lastChild];
	}
	
	public function leave(\CommonMark\Interfaces\IVisitable $node) {}
});

var_dump($visited);
?>
--EXPECT--
array(0) {
}
array(3) {
  [0]=>
  object(CommonMark\Node\Document)#1 (1) {
    ["children"]=>
    array(1) {
      [0]=>
      object(CommonMark\Node\Paragraph)#2 (1) {
        ["children"]=>
        array(1) {
          [0]=>
          object(CommonMark\Node\Text)#3 (1) {
            ["literal"]=>
            string(0) ""
          }
        }
      }
    }
  }
  [1]=>
  object(CommonMark\Node\Paragraph)#2 (1) {
    ["children"]=>
    array(1) {
      [0]=>
      object(CommonMark\Node\Text)#3 (1) {
        ["literal"]=>
        string(0) ""
      }
    }
  }
  [2]=>
  object(CommonMark\Node\Text)#3 (1) {
    ["literal"]=>
    string(0) ""
  }
}
array(1) {
  [0]=>
  string(24) "CommonMark\Node\Document"
}
array(1) {
  [0]=>
  string(24) "CommonMark\Node\Document"
}
array(4) {
  [0]=>
  string(26) "CommonMark\Node\BulletList"
  [1]=>
  string(20) "CommonMark\Node\Item"
  [2]=>
  string(20) "CommonMark\Node\Item"
  [3]=>
  string(20) "CommonMark\Node\Item"
}


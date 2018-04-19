--TEST--
CommonMark\CQL compiler (begin + 2)
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
  * hello hell
  * hello world
EOD
);

$call = new \CommonMark\CQL(<<<EOD
/firstChild(List)[
	/firstChild/next
]
EOD
);

$text = new \CommonMark\CQL("
/firstChild(Paragraph)[
  /firstChild(Text)
]");

$getText = function ($node) use ($text) {
	$result = null;
	$text($node, function($root, $text) use(&$result) {
		$result = $text->literal;
	});
	return $result;
};

$call($doc, function($root, $node) use ($getText) {
	if ($node instanceof \CommonMark\Node\Item) {
		if ($getText($node) == "hello world") {
			echo "OK";
		}
	}
});
?>
--EXPECT--
OK
